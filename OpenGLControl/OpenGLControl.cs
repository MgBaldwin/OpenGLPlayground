using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OpenGLControl
{
    public partial class OpenGLControl: UserControl
    {
        OpenGLWrapper.OpenGLWindowWrapper m_Window = new OpenGLWrapper.OpenGLWindowWrapper();

        public OpenGLControl()
        {
            InitializeComponent();
        }

        private void OpenGLControl_Load(object sender, EventArgs e)
        {
            m_Window.Create(this.Handle);
            m_Window.Resize(this.Width, this.Height);
        }

        private void OpenGLControl_SizeChanged(object sender, EventArgs e)
        {
            m_Window.Resize(this.Width, this.Height);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            m_Window.Draw();
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }
    }
}
