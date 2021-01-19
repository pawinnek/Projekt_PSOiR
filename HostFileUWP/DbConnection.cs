using MongoDB.Bson;
using MongoDB.Driver;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HostFileUWP
{
    class DbConnection
    {
        MongoClient dbClient = new MongoClient("mongodb://localhost:27017/?readPreference=primary&appname=MongoDB%20Compass&ssl=false");
        public IMongoCollection<BsonDocument> collection;
        public DbConnection()
        {
            var db = dbClient.GetDatabase("HostAppFiles");
            collection = db.GetCollection<BsonDocument>("Files");
        }

        public void SendFile(Guid userUuid, Guid fileUuid, Byte[] file, string filename)
        {
            BsonDocument document = new BsonDocument { { "fileid", fileUuid.ToByteArray() },
                {
                    "file", new BsonDocument { {"filename", filename}, { "file", file } }
                }
            };
            collection.InsertOne(document);
        }

    }
}
