using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace HostFileUWP
{
    class Master
    {
        static string malePath = @"C:\Users\Troll\Downloads\zadanie-2-Sobczyk-239086.c";
        static string sredniePath = @"C:\Users\Troll\Downloads\pl-dict.oxt";
        static string duzePath = @"C:\Users\Troll\Downloads\drugsCom_raw.zip";

        private Thread me;

        public  List<Worker> Workers { get; set; }

        public Master()
        {
            me = Thread.CurrentThread;
            me.Name = "MainThread";
            Workers = new List<Worker>();
        }

        /// <summary>
        /// Adds Worker to list
        /// </summary>
        /// <param name="worker"></param>
        public void AddWorker(Worker worker)
        {
            Workers.Add(worker);
        }

        /// <summary>
        /// Static generator for designed system
        /// </summary>
        /// <returns></returns>
        public static Master CreateClassicVariant()
        {
            Master master = new Master();
            for(int i = 0; i < 5; i++)
            {
                var worker = new Worker();
                master.AddWorker(worker);
            }
            return master;
        }
    }
}
