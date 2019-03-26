using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace ThemeEditor
{
	/// <summary>
	/// Summary description for frmPreview.
	/// </summary>
	public class frmPreview : System.Windows.Forms.Form
	{
		private System.Windows.Forms.PictureBox picPreview;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public frmPreview()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.picPreview = new System.Windows.Forms.PictureBox();
			this.SuspendLayout();
			// 
			// picPreview
			// 
			this.picPreview.Location = new System.Drawing.Point(0, 0);
			this.picPreview.Name = "picPreview";
			this.picPreview.Size = new System.Drawing.Size(512, 512);
			this.picPreview.TabIndex = 0;
			this.picPreview.TabStop = false;
			this.picPreview.Click += new System.EventHandler(this.picPreview_Click);
			// 
			// frmPreview
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(512, 513);
			this.Controls.Add(this.picPreview);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "frmPreview";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Background Preview";
			this.ResumeLayout(false);

		}
		#endregion

		public void SetPhoto(string file)
		{
			picPreview.Image=System.Drawing.Image.FromFile(file);
		}

		private void picPreview_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}
	}
}
