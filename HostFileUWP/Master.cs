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
        //static string malePath = @"C:\Users\Troll\Downloads\zadanie-2-Sobczyk-239086.c";
        //static string sredniePath = @"C:\Users\Troll\Downloads\pl-dict.oxt";
        //static string duzePath = @"C:\Users\Troll\Downloads\drugsCom_raw.zip";

        public string[] guids = { "7bbc6a1d-24af-4394-853d-76f2a6585cb8", "c7b89c4f-2e5a-4ba3-a2a7-0aba4d731945", "55d28c56-998b-4766-b4e9-b657ab2015a8", "e903d8c7-5195-4361-8816-380c2eec4104", "e1d55efb-acb2-489e-8d37-a17d8325edbd" };

        public Queue<Tuple<string, string>> Tasks = new Queue<Tuple<string, string>>(); // size, OwnerId

        private Thread me;

        public List<Worker> Workers { get; set; }

        public Master()
        {
            //ThreadStart ts = new ThreadStart();
            Workers = new List<Worker>();
            CreateClassicVariant();
        }

        /// <summary>
        /// Adds Worker to list
        /// </summary>
        /// <param name="worker"></param>
        public void AddWorker(Worker worker)
        {
            Workers.Add(worker);
        }

        public void CreateClassicVariant()
        {
            //Master master = new Master();
            for (int i = 0; i < 5; i++)
            {
                var worker = new Worker(guids[i]);
                AddWorker(worker);
            }
        }

        bool zzz = true;

        public void Stop()
        {
            zzz = false;
        }

        public void Run()
        {
            zzz = true;
            if (me == null || me.ThreadState != ThreadState.Running)
            {
                me = new Thread(() => KingsOrder());
                me.Priority = ThreadPriority.Highest;
                me.Start();
            }
                
        }

        public ThreadState State()
        {
            if (me == null)
                return ThreadState.Unstarted;
            return me.ThreadState;
        }

        private void KingsOrder()
        {
            while (zzz)
                if (Tasks.Count > 0)
                    foreach (var worker in Workers)
                    {
                        if (Tasks.Count > 0)
                        {

                            var val = Tasks.Peek();
                            if (worker.Run(val.Item1, val.Item2))
                                Tasks.Dequeue();
                        }

                    }
                else
                    break;
        }


    }
}
