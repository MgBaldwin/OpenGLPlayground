using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OpenGLPlayground
{
    public partial class Form1 : Form
    {
        OpenGLControl.OpenGLControl m_OpenGLControl = new OpenGLControl.OpenGLControl();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Controls.Add(m_OpenGLControl);
            m_OpenGLControl.Dock = DockStyle.Fill;
        }
    }
}
