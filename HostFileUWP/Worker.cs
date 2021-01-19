using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace HostFileUWP
{
    class Worker
    {
        private const string malePath = @"C:\Users\Troll\Downloads\zadanie-2-Sobczyk-239086.c";
        private const string sredniePath = @"C:\Users\Troll\Downloads\pl-dict.oxt";
        private const string duzePath = @"C:\Users\Troll\Downloads\drugsCom_raw.zip";

        private bool isBusy;

        DbConnection dbConnection;

        private Thread me;

        // Wszelie inne opcje beda dziedziczyc po tym i nadpisywac Call To Arms xD
        public void CallToArms()
        {
            
            readBytes();
            isBusy = false;
        }

        public Worker()
        {
            dbConnection = new DbConnection();
            ThreadStart ts = new ThreadStart(CallToArms);
            me = new Thread(ts);
        }

        public void Run()
        {

            isBusy = true;
        }

        private byte[] readBytes()
        {
            throw new NotImplementedException();
        }
    }
}
