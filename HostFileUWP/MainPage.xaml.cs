using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace HostFileUWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public int filesQtyToAdd;
        Master masterThread;

        string client;

        public MainPage()
        {
            masterThread = new Master();
            this.InitializeComponent();
        }

        private void male_Click(object sender, RoutedEventArgs e)
        {
            if (client != null)
                for (int i = 0; i < filesQtyToAdd; i++)
                    masterThread.Tasks.Enqueue(new Tuple<string, string>("male", client));
        }

        private void duze_Click(object sender, RoutedEventArgs e)
        {
            if (client != null)
                for (int i = 0; i < filesQtyToAdd; i++)
                    masterThread.Tasks.Enqueue(new Tuple<string, string>("duze", client));
        }

        private void srednie_Click(object sender, RoutedEventArgs e)
        {
            if (client != null)
                for(int i = 0; i < filesQtyToAdd; i ++)
                    masterThread.Tasks.Enqueue(new Tuple<string, string>("srednie", client));
        }

        private void SwitchcState_Click(object sender, RoutedEventArgs e)
        {
            if (masterThread.State() == ThreadState.Running)
                masterThread.Stop();
            else
                masterThread.Run();
        }
    }
}
