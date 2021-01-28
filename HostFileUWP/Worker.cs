using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;

namespace HostFileUWP
{
    class Worker
    {
        private const string malePath = @".\zadanie-2-Sobczyk-239086.c";
        private const string sredniePath = @".\pl-dict.oxt";
        private const string duzePath = @".\drugsCom_raw.zip";

        Guid myGuid;

        public bool isBusy;

        string connectionString; // = "mongodb://localhost:27017/?readPreference=primary&appname=MongoDB%20Compass&ssl=false";


        public Thread thread;
        private string size;
        private string owner;


        // Wszelie inne opcje beda dziedziczyc po tym i nadpisywac.
        public void CallToArms()
        {
            byte[] file = null;
            
            // Część odpowiedzialna za przyjęcie pliku, zastepująca odbieraniae go od klienta
            if (size == "male")
                file = File.ReadAllBytes(malePath);
            else if (size == "srednie")
                file = File.ReadAllBytes(sredniePath);
            else if (size == "duze")
                file = File.ReadAllBytes(duzePath);
            MongoClient dbClient = new MongoClient(connectionString); // do wyciągania z queue
            var database = dbClient.GetDatabase("HostAppFiles");
            var collection = database.GetCollection<BsonDocument>("Files");


            // Część odpowiedzialna za wysłanie pliku do bazy
            var fileGuid = System.Guid.NewGuid();
            var ownerGuuid = System.Guid.Parse(owner);
            BsonDocument document = new BsonDocument { { "guid", MongoDB.Bson.GuidConverter.ToBytes(fileGuid, GuidRepresentation.Standard) } , { "Owner", MongoDB.Bson.GuidConverter.ToBytes(fileGuid, GuidRepresentation.Standard) } ,{ "file", file }
            };
            collection.InsertOne(document);
        }

        public Worker(string conn)
        {
            connectionString = conn;
            //ThreadStart ts = new ThreadStart(() => CallToArms());
            //thread = new Thread(ts);
            
        }

        public bool Run(string size, string guid)
        {
            if (thread == null || thread.ThreadState != ThreadState.Running)
            { 
                this.owner = guid;
                this.size = size;
                Run();
                return true;
            }
            return false;
        }

        bool zzz = true;

        public void Stop()
        {
            zzz = false;
        }

        private void Run()
        {
            zzz = true;
            if (thread == null || thread.ThreadState != ThreadState.Running)
            {
                thread = new Thread(() => CallToArms());
                thread.Priority = ThreadPriority.Highest;
                thread.Start();
            }

        }

        public ThreadState State()
        {
            if (thread == null)
                return ThreadState.Unstarted;
            return thread.ThreadState;
        }
    }
}
