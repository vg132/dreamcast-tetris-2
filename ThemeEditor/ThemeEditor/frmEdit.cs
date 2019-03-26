using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace ThemeEditor
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmThemeEditor : System.Windows.Forms.Form
	{
		private Theme m_CurrentTheme=null;
		private FileIO m_FileIO=new FileIO();
		private System.Windows.Forms.TextBox txtName;
		private System.Windows.Forms.TextBox txtArtist;
		private System.Windows.Forms.TextBox txtURL;
		private System.Windows.Forms.TextBox txtFileName;
		private System.Windows.Forms.TextBox txtStartLine;
		private System.Windows.Forms.Label lblName;
		private System.Windows.Forms.Label lblArtist;
		private System.Windows.Forms.Label lblURL;
		private System.Windows.Forms.Label lblFileName;
		private System.Windows.Forms.Label lblDescription;
		private System.Windows.Forms.Label lblStartLine;
		private System.Windows.Forms.TextBox txtDescription;
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.GroupBox grpBackground;
		private System.Windows.Forms.MenuItem menuFile;
		private System.Windows.Forms.MenuItem menuFileNew;
		private System.Windows.Forms.MenuItem menuFileOpen;
		private System.Windows.Forms.MenuItem menuFileClose;
		private System.Windows.Forms.MenuItem menuFileSep1;
		private System.Windows.Forms.MenuItem menuFileSave;
		private System.Windows.Forms.MenuItem menuFileSaveAs;
		private System.Windows.Forms.MenuItem menuFileSep2;
		private System.Windows.Forms.MenuItem menuFileExit;
		private System.Windows.Forms.GroupBox grpTreeView;
		private System.Windows.Forms.TreeView trvTheme;
		private System.Windows.Forms.ImageList imageListTreeView;
		private System.Windows.Forms.GroupBox grpThemeInfo;
		private System.Windows.Forms.TextBox txtAboutName;
		private System.Windows.Forms.Label lblAboutName;
		private System.Windows.Forms.Label lblAboutAuthor;
		private System.Windows.Forms.Label lblAboutEmail;
		private System.Windows.Forms.Label lblAboutURL;
		private System.Windows.Forms.Label lblAboutDescription;
		private System.Windows.Forms.TextBox txtAboutAuthor;
		private System.Windows.Forms.TextBox txtAboutEmail;
		private System.Windows.Forms.TextBox txtAboutURL;
		private System.Windows.Forms.TextBox txtAboutDescription;
		private System.Windows.Forms.Button btnBrowse;
		private System.Windows.Forms.Button btnViewImage;
		private System.Windows.Forms.MenuItem menuEdit;
		private System.Windows.Forms.MenuItem menuEditAddBackground;
		private System.Windows.Forms.MenuItem menuEditRemoveBackground;
		private System.Windows.Forms.MenuItem menuHelp;
		private System.Windows.Forms.MenuItem menuHelpHelp;
		private System.Windows.Forms.ContextMenu contextMenuTreeView;
		private System.Windows.Forms.MenuItem contextMenuAddBackground;
		private System.Windows.Forms.MenuItem contextMenuRemoveBackground;
		private System.ComponentModel.IContainer components;

		public frmThemeEditor()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			EnableControls(false);
			grpBackground.Location=new Point(184,500);
			grpThemeInfo.Location=new Point(184,8);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
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
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(frmThemeEditor));
			this.grpBackground = new System.Windows.Forms.GroupBox();
			this.btnViewImage = new System.Windows.Forms.Button();
			this.btnBrowse = new System.Windows.Forms.Button();
			this.txtDescription = new System.Windows.Forms.TextBox();
			this.lblStartLine = new System.Windows.Forms.Label();
			this.lblDescription = new System.Windows.Forms.Label();
			this.lblFileName = new System.Windows.Forms.Label();
			this.lblURL = new System.Windows.Forms.Label();
			this.lblArtist = new System.Windows.Forms.Label();
			this.lblName = new System.Windows.Forms.Label();
			this.txtStartLine = new System.Windows.Forms.TextBox();
			this.txtFileName = new System.Windows.Forms.TextBox();
			this.txtURL = new System.Windows.Forms.TextBox();
			this.txtArtist = new System.Windows.Forms.TextBox();
			this.txtName = new System.Windows.Forms.TextBox();
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.menuFile = new System.Windows.Forms.MenuItem();
			this.menuFileNew = new System.Windows.Forms.MenuItem();
			this.menuFileOpen = new System.Windows.Forms.MenuItem();
			this.menuFileClose = new System.Windows.Forms.MenuItem();
			this.menuFileSep1 = new System.Windows.Forms.MenuItem();
			this.menuFileSave = new System.Windows.Forms.MenuItem();
			this.menuFileSaveAs = new System.Windows.Forms.MenuItem();
			this.menuFileSep2 = new System.Windows.Forms.MenuItem();
			this.menuFileExit = new System.Windows.Forms.MenuItem();
			this.menuEdit = new System.Windows.Forms.MenuItem();
			this.menuEditAddBackground = new System.Windows.Forms.MenuItem();
			this.menuEditRemoveBackground = new System.Windows.Forms.MenuItem();
			this.menuHelp = new System.Windows.Forms.MenuItem();
			this.menuHelpHelp = new System.Windows.Forms.MenuItem();
			this.grpTreeView = new System.Windows.Forms.GroupBox();
			this.trvTheme = new System.Windows.Forms.TreeView();
			this.contextMenuTreeView = new System.Windows.Forms.ContextMenu();
			this.contextMenuAddBackground = new System.Windows.Forms.MenuItem();
			this.contextMenuRemoveBackground = new System.Windows.Forms.MenuItem();
			this.imageListTreeView = new System.Windows.Forms.ImageList(this.components);
			this.grpThemeInfo = new System.Windows.Forms.GroupBox();
			this.lblAboutDescription = new System.Windows.Forms.Label();
			this.lblAboutURL = new System.Windows.Forms.Label();
			this.lblAboutEmail = new System.Windows.Forms.Label();
			this.lblAboutAuthor = new System.Windows.Forms.Label();
			this.lblAboutName = new System.Windows.Forms.Label();
			this.txtAboutDescription = new System.Windows.Forms.TextBox();
			this.txtAboutURL = new System.Windows.Forms.TextBox();
			this.txtAboutEmail = new System.Windows.Forms.TextBox();
			this.txtAboutAuthor = new System.Windows.Forms.TextBox();
			this.txtAboutName = new System.Windows.Forms.TextBox();
			this.grpBackground.SuspendLayout();
			this.grpTreeView.SuspendLayout();
			this.grpThemeInfo.SuspendLayout();
			this.SuspendLayout();
			// 
			// grpBackground
			// 
			this.grpBackground.Controls.Add(this.btnViewImage);
			this.grpBackground.Controls.Add(this.btnBrowse);
			this.grpBackground.Controls.Add(this.txtDescription);
			this.grpBackground.Controls.Add(this.lblStartLine);
			this.grpBackground.Controls.Add(this.lblDescription);
			this.grpBackground.Controls.Add(this.lblFileName);
			this.grpBackground.Controls.Add(this.lblURL);
			this.grpBackground.Controls.Add(this.lblArtist);
			this.grpBackground.Controls.Add(this.lblName);
			this.grpBackground.Controls.Add(this.txtStartLine);
			this.grpBackground.Controls.Add(this.txtFileName);
			this.grpBackground.Controls.Add(this.txtURL);
			this.grpBackground.Controls.Add(this.txtArtist);
			this.grpBackground.Controls.Add(this.txtName);
			this.grpBackground.Location = new System.Drawing.Point(184, 500);
			this.grpBackground.Name = "grpBackground";
			this.grpBackground.Size = new System.Drawing.Size(304, 240);
			this.grpBackground.TabIndex = 1;
			this.grpBackground.TabStop = false;
			this.grpBackground.Text = "Background";
			// 
			// btnViewImage
			// 
			this.btnViewImage.Location = new System.Drawing.Point(216, 208);
			this.btnViewImage.Name = "btnViewImage";
			this.btnViewImage.TabIndex = 14;
			this.btnViewImage.Text = "View Image";
			this.btnViewImage.Click += new System.EventHandler(this.btnViewImage_Click);
			// 
			// btnBrowse
			// 
			this.btnBrowse.Location = new System.Drawing.Point(266, 95);
			this.btnBrowse.Name = "btnBrowse";
			this.btnBrowse.Size = new System.Drawing.Size(22, 23);
			this.btnBrowse.TabIndex = 13;
			this.btnBrowse.Text = "...";
			this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
			// 
			// txtDescription
			// 
			this.txtDescription.Location = new System.Drawing.Point(80, 144);
			this.txtDescription.Name = "txtDescription";
			this.txtDescription.Size = new System.Drawing.Size(208, 20);
			this.txtDescription.TabIndex = 11;
			this.txtDescription.Text = "";
			// 
			// lblStartLine
			// 
			this.lblStartLine.Location = new System.Drawing.Point(8, 122);
			this.lblStartLine.Name = "lblStartLine";
			this.lblStartLine.Size = new System.Drawing.Size(64, 16);
			this.lblStartLine.TabIndex = 10;
			this.lblStartLine.Text = "Start Line:";
			this.lblStartLine.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblDescription
			// 
			this.lblDescription.Location = new System.Drawing.Point(8, 146);
			this.lblDescription.Name = "lblDescription";
			this.lblDescription.Size = new System.Drawing.Size(64, 16);
			this.lblDescription.TabIndex = 9;
			this.lblDescription.Text = "Description:";
			this.lblDescription.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblFileName
			// 
			this.lblFileName.Location = new System.Drawing.Point(8, 98);
			this.lblFileName.Name = "lblFileName";
			this.lblFileName.Size = new System.Drawing.Size(64, 16);
			this.lblFileName.TabIndex = 8;
			this.lblFileName.Text = "File Name:";
			this.lblFileName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblURL
			// 
			this.lblURL.Location = new System.Drawing.Point(8, 74);
			this.lblURL.Name = "lblURL";
			this.lblURL.Size = new System.Drawing.Size(64, 16);
			this.lblURL.TabIndex = 7;
			this.lblURL.Text = "URL:";
			this.lblURL.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblArtist
			// 
			this.lblArtist.Location = new System.Drawing.Point(8, 50);
			this.lblArtist.Name = "lblArtist";
			this.lblArtist.Size = new System.Drawing.Size(64, 16);
			this.lblArtist.TabIndex = 6;
			this.lblArtist.Text = "Artist:";
			this.lblArtist.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblName
			// 
			this.lblName.Location = new System.Drawing.Point(8, 24);
			this.lblName.Name = "lblName";
			this.lblName.Size = new System.Drawing.Size(64, 16);
			this.lblName.TabIndex = 5;
			this.lblName.Text = "Name:";
			this.lblName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// txtStartLine
			// 
			this.txtStartLine.Location = new System.Drawing.Point(80, 120);
			this.txtStartLine.Name = "txtStartLine";
			this.txtStartLine.Size = new System.Drawing.Size(208, 20);
			this.txtStartLine.TabIndex = 4;
			this.txtStartLine.Text = "";
			// 
			// txtFileName
			// 
			this.txtFileName.Location = new System.Drawing.Point(80, 96);
			this.txtFileName.Name = "txtFileName";
			this.txtFileName.Size = new System.Drawing.Size(184, 20);
			this.txtFileName.TabIndex = 3;
			this.txtFileName.Text = "";
			// 
			// txtURL
			// 
			this.txtURL.Location = new System.Drawing.Point(80, 72);
			this.txtURL.Name = "txtURL";
			this.txtURL.Size = new System.Drawing.Size(208, 20);
			this.txtURL.TabIndex = 2;
			this.txtURL.Text = "";
			// 
			// txtArtist
			// 
			this.txtArtist.Location = new System.Drawing.Point(80, 48);
			this.txtArtist.Name = "txtArtist";
			this.txtArtist.Size = new System.Drawing.Size(208, 20);
			this.txtArtist.TabIndex = 1;
			this.txtArtist.Text = "";
			// 
			// txtName
			// 
			this.txtName.Location = new System.Drawing.Point(80, 22);
			this.txtName.Name = "txtName";
			this.txtName.Size = new System.Drawing.Size(208, 20);
			this.txtName.TabIndex = 0;
			this.txtName.Text = "";
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																																						 this.menuFile,
																																						 this.menuEdit,
																																						 this.menuHelp});
			// 
			// menuFile
			// 
			this.menuFile.Index = 0;
			this.menuFile.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																																						 this.menuFileNew,
																																						 this.menuFileOpen,
																																						 this.menuFileClose,
																																						 this.menuFileSep1,
																																						 this.menuFileSave,
																																						 this.menuFileSaveAs,
																																						 this.menuFileSep2,
																																						 this.menuFileExit});
			this.menuFile.Text = "&File";
			// 
			// menuFileNew
			// 
			this.menuFileNew.Index = 0;
			this.menuFileNew.Shortcut = System.Windows.Forms.Shortcut.CtrlN;
			this.menuFileNew.Text = "&New";
			this.menuFileNew.Click += new System.EventHandler(this.menuFileNew_Click);
			// 
			// menuFileOpen
			// 
			this.menuFileOpen.Index = 1;
			this.menuFileOpen.Shortcut = System.Windows.Forms.Shortcut.CtrlO;
			this.menuFileOpen.Text = "&Open...";
			this.menuFileOpen.Click += new System.EventHandler(this.menuFileOpen_Click);
			// 
			// menuFileClose
			// 
			this.menuFileClose.Enabled = false;
			this.menuFileClose.Index = 2;
			this.menuFileClose.Text = "Close";
			this.menuFileClose.Click += new System.EventHandler(this.menuFileClose_Click);
			// 
			// menuFileSep1
			// 
			this.menuFileSep1.Index = 3;
			this.menuFileSep1.Text = "-";
			// 
			// menuFileSave
			// 
			this.menuFileSave.Enabled = false;
			this.menuFileSave.Index = 4;
			this.menuFileSave.Shortcut = System.Windows.Forms.Shortcut.CtrlS;
			this.menuFileSave.Text = "&Save";
			this.menuFileSave.Click += new System.EventHandler(this.menuFileSave_Click);
			// 
			// menuFileSaveAs
			// 
			this.menuFileSaveAs.Enabled = false;
			this.menuFileSaveAs.Index = 5;
			this.menuFileSaveAs.Text = "Save as...";
			this.menuFileSaveAs.Click += new System.EventHandler(this.menuFileSaveAs_Click);
			// 
			// menuFileSep2
			// 
			this.menuFileSep2.Index = 6;
			this.menuFileSep2.Text = "-";
			// 
			// menuFileExit
			// 
			this.menuFileExit.Index = 7;
			this.menuFileExit.Shortcut = System.Windows.Forms.Shortcut.CtrlX;
			this.menuFileExit.Text = "E&xit";
			this.menuFileExit.Click += new System.EventHandler(this.menuFileExit_Click);
			// 
			// menuEdit
			// 
			this.menuEdit.Index = 1;
			this.menuEdit.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																																						 this.menuEditAddBackground,
																																						 this.menuEditRemoveBackground});
			this.menuEdit.Text = "&Edit";
			// 
			// menuEditAddBackground
			// 
			this.menuEditAddBackground.Index = 0;
			this.menuEditAddBackground.Text = "Add Background";
			this.menuEditAddBackground.Click += new System.EventHandler(this.menuEditAddBackground_Click);
			// 
			// menuEditRemoveBackground
			// 
			this.menuEditRemoveBackground.Index = 1;
			this.menuEditRemoveBackground.Text = "Remove Background";
			this.menuEditRemoveBackground.Click += new System.EventHandler(this.menuEditRemoveBackground_Click);
			// 
			// menuHelp
			// 
			this.menuHelp.Index = 2;
			this.menuHelp.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																																						 this.menuHelpHelp});
			this.menuHelp.Text = "&Help";
			// 
			// menuHelpHelp
			// 
			this.menuHelpHelp.Index = 0;
			this.menuHelpHelp.Text = "Help...";
			// 
			// grpTreeView
			// 
			this.grpTreeView.Controls.Add(this.trvTheme);
			this.grpTreeView.Location = new System.Drawing.Point(8, 8);
			this.grpTreeView.Name = "grpTreeView";
			this.grpTreeView.Size = new System.Drawing.Size(178, 240);
			this.grpTreeView.TabIndex = 2;
			this.grpTreeView.TabStop = false;
			this.grpTreeView.Text = "Theme";
			// 
			// trvTheme
			// 
			this.trvTheme.ContextMenu = this.contextMenuTreeView;
			this.trvTheme.HideSelection = false;
			this.trvTheme.ImageList = this.imageListTreeView;
			this.trvTheme.Indent = 15;
			this.trvTheme.Location = new System.Drawing.Point(8, 24);
			this.trvTheme.Name = "trvTheme";
			this.trvTheme.Size = new System.Drawing.Size(160, 208);
			this.trvTheme.TabIndex = 0;
			this.trvTheme.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.trvTheme_AfterSelect);
			this.trvTheme.BeforeSelect += new System.Windows.Forms.TreeViewCancelEventHandler(this.trvTheme_BeforeSelect);
			// 
			// contextMenuTreeView
			// 
			this.contextMenuTreeView.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																																												this.contextMenuAddBackground,
																																												this.contextMenuRemoveBackground});
			// 
			// contextMenuAddBackground
			// 
			this.contextMenuAddBackground.Index = 0;
			this.contextMenuAddBackground.Text = "Add Background";
			this.contextMenuAddBackground.Click += new System.EventHandler(this.menuEditAddBackground_Click);
			// 
			// contextMenuRemoveBackground
			// 
			this.contextMenuRemoveBackground.Index = 1;
			this.contextMenuRemoveBackground.Text = "Remove Background";
			this.contextMenuRemoveBackground.Click += new System.EventHandler(this.menuEditRemoveBackground_Click);
			// 
			// imageListTreeView
			// 
			this.imageListTreeView.ColorDepth = System.Windows.Forms.ColorDepth.Depth16Bit;
			this.imageListTreeView.ImageSize = new System.Drawing.Size(16, 16);
			this.imageListTreeView.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListTreeView.ImageStream")));
			this.imageListTreeView.TransparentColor = System.Drawing.Color.Silver;
			// 
			// grpThemeInfo
			// 
			this.grpThemeInfo.Controls.Add(this.lblAboutDescription);
			this.grpThemeInfo.Controls.Add(this.lblAboutURL);
			this.grpThemeInfo.Controls.Add(this.lblAboutEmail);
			this.grpThemeInfo.Controls.Add(this.lblAboutAuthor);
			this.grpThemeInfo.Controls.Add(this.lblAboutName);
			this.grpThemeInfo.Controls.Add(this.txtAboutDescription);
			this.grpThemeInfo.Controls.Add(this.txtAboutURL);
			this.grpThemeInfo.Controls.Add(this.txtAboutEmail);
			this.grpThemeInfo.Controls.Add(this.txtAboutAuthor);
			this.grpThemeInfo.Controls.Add(this.txtAboutName);
			this.grpThemeInfo.Location = new System.Drawing.Point(184, 8);
			this.grpThemeInfo.Name = "grpThemeInfo";
			this.grpThemeInfo.Size = new System.Drawing.Size(304, 240);
			this.grpThemeInfo.TabIndex = 3;
			this.grpThemeInfo.TabStop = false;
			this.grpThemeInfo.Text = "Theme Info";
			// 
			// lblAboutDescription
			// 
			this.lblAboutDescription.Location = new System.Drawing.Point(16, 122);
			this.lblAboutDescription.Name = "lblAboutDescription";
			this.lblAboutDescription.Size = new System.Drawing.Size(72, 16);
			this.lblAboutDescription.TabIndex = 9;
			this.lblAboutDescription.Text = "Description:";
			// 
			// lblAboutURL
			// 
			this.lblAboutURL.Location = new System.Drawing.Point(16, 98);
			this.lblAboutURL.Name = "lblAboutURL";
			this.lblAboutURL.Size = new System.Drawing.Size(72, 16);
			this.lblAboutURL.TabIndex = 8;
			this.lblAboutURL.Text = "URL:";
			// 
			// lblAboutEmail
			// 
			this.lblAboutEmail.Location = new System.Drawing.Point(16, 74);
			this.lblAboutEmail.Name = "lblAboutEmail";
			this.lblAboutEmail.Size = new System.Drawing.Size(72, 16);
			this.lblAboutEmail.TabIndex = 7;
			this.lblAboutEmail.Text = "Email:";
			// 
			// lblAboutAuthor
			// 
			this.lblAboutAuthor.Location = new System.Drawing.Point(16, 50);
			this.lblAboutAuthor.Name = "lblAboutAuthor";
			this.lblAboutAuthor.Size = new System.Drawing.Size(72, 16);
			this.lblAboutAuthor.TabIndex = 6;
			this.lblAboutAuthor.Text = "Author:";
			// 
			// lblAboutName
			// 
			this.lblAboutName.Location = new System.Drawing.Point(16, 26);
			this.lblAboutName.Name = "lblAboutName";
			this.lblAboutName.Size = new System.Drawing.Size(72, 16);
			this.lblAboutName.TabIndex = 5;
			this.lblAboutName.Text = "Name:";
			// 
			// txtAboutDescription
			// 
			this.txtAboutDescription.Location = new System.Drawing.Point(94, 120);
			this.txtAboutDescription.Name = "txtAboutDescription";
			this.txtAboutDescription.Size = new System.Drawing.Size(192, 20);
			this.txtAboutDescription.TabIndex = 4;
			this.txtAboutDescription.Text = "";
			// 
			// txtAboutURL
			// 
			this.txtAboutURL.Location = new System.Drawing.Point(94, 96);
			this.txtAboutURL.Name = "txtAboutURL";
			this.txtAboutURL.Size = new System.Drawing.Size(192, 20);
			this.txtAboutURL.TabIndex = 3;
			this.txtAboutURL.Text = "";
			// 
			// txtAboutEmail
			// 
			this.txtAboutEmail.Location = new System.Drawing.Point(94, 72);
			this.txtAboutEmail.Name = "txtAboutEmail";
			this.txtAboutEmail.Size = new System.Drawing.Size(192, 20);
			this.txtAboutEmail.TabIndex = 2;
			this.txtAboutEmail.Text = "";
			// 
			// txtAboutAuthor
			// 
			this.txtAboutAuthor.Location = new System.Drawing.Point(94, 48);
			this.txtAboutAuthor.Name = "txtAboutAuthor";
			this.txtAboutAuthor.Size = new System.Drawing.Size(192, 20);
			this.txtAboutAuthor.TabIndex = 1;
			this.txtAboutAuthor.Text = "";
			// 
			// txtAboutName
			// 
			this.txtAboutName.Location = new System.Drawing.Point(94, 24);
			this.txtAboutName.Name = "txtAboutName";
			this.txtAboutName.Size = new System.Drawing.Size(192, 20);
			this.txtAboutName.TabIndex = 0;
			this.txtAboutName.Text = "";
			// 
			// frmThemeEditor
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(504, 260);
			this.Controls.Add(this.grpThemeInfo);
			this.Controls.Add(this.grpTreeView);
			this.Controls.Add(this.grpBackground);
			this.MaximizeBox = false;
			this.Menu = this.mainMenu;
			this.Name = "frmThemeEditor";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Tetris 2 Theme Editor - VG Software";
			this.grpBackground.ResumeLayout(false);
			this.grpTreeView.ResumeLayout(false);
			this.grpThemeInfo.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmThemeEditor());
		}

		private void menuFileOpen_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog ofd=new OpenFileDialog();
			ofd.Filter="Tetris Theme File (*.theme)|*.theme";
			if(ofd.ShowDialog()==DialogResult.OK)
			{
				Cursor.Current=Cursors.WaitCursor;
				m_CurrentTheme=m_FileIO.ReadFile(ofd.FileName);
				BuildTree();
				EnableControls(true);
				txtAboutName.Text=m_CurrentTheme.Name;
				txtAboutAuthor.Text=m_CurrentTheme.Author;
				txtAboutEmail.Text=m_CurrentTheme.Email;
				txtAboutURL.Text=m_CurrentTheme.URL;
				txtAboutDescription.Text=m_CurrentTheme.Description;
				grpBackground.Location=new Point(184,500);
				grpThemeInfo.Location=new Point(184,8);
				Cursor.Current=Cursors.Default;
			}
		}

		private void BuildTree()
		{
			trvTheme.Nodes.Clear();
			TreeNode root=null;
			if(m_CurrentTheme.Name==null)
				root=new TreeNode("Theme");
			else
				root=new TreeNode(m_CurrentTheme.Name);
			root.SelectedImageIndex=1;
			root.ImageIndex=0;
			root.Tag=null;


			TreeNode node=null;
			foreach(Background background in m_CurrentTheme.GetBackgrounds())
			{
				node=new TreeNode(background.Name);
				node.ImageIndex=2;
				node.SelectedImageIndex=2;
				node.Tag=background;
				root.Nodes.Add(node);
			}
			trvTheme.Nodes.Add(root);
			trvTheme.ExpandAll();
		}

		private void menuFileExit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}

		private void menuFileClose_Click(object sender, System.EventArgs e)
		{
			trvTheme.Nodes.Clear();
			m_CurrentTheme=null;
			EnableControls(false);
			txtAboutName.Text="";
			txtAboutAuthor.Text="";
			txtAboutEmail.Text="";
			txtAboutURL.Text="";
			txtAboutDescription.Text="";
			grpBackground.Location=new Point(184,500);
			grpThemeInfo.Location=new Point(184,8);
		}

		private void EnableControls(bool enable)
		{
			menuFileClose.Enabled=enable;
			menuFileSave.Enabled=enable;
			menuFileSaveAs.Enabled=enable;
			grpTreeView.Enabled=enable;
			grpBackground.Enabled=enable;
			grpThemeInfo.Enabled=enable;
			menuEditAddBackground.Enabled=enable;
			menuEditRemoveBackground.Enabled=enable;
			contextMenuAddBackground.Enabled=enable;
			contextMenuRemoveBackground.Enabled=enable;
		}

		private void trvTheme_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			if(trvTheme.SelectedNode.Tag!=null)
			{
				Background bg=(Background)trvTheme.SelectedNode.Tag;
				txtName.Text=bg.Name;
				txtArtist.Text=bg.Artist;
				txtURL.Text=bg.URL;
				txtFileName.Text=bg.Path;
				txtStartLine.Text=bg.StartLine;
				txtDescription.Text=bg.Description;
				grpThemeInfo.Location=new Point(184,500);
				grpBackground.Location=new Point(184,8);
			}
			else
			{
				txtAboutName.Text=m_CurrentTheme.Name;
				txtAboutAuthor.Text=m_CurrentTheme.Author;
				txtAboutEmail.Text=m_CurrentTheme.Email;
				txtAboutURL.Text=m_CurrentTheme.URL;
				txtAboutDescription.Text=m_CurrentTheme.Description;
				grpBackground.Location=new Point(184,500);
				grpThemeInfo.Location=new Point(184,8);
			}
		}

		private void menuFileSave_Click(object sender, System.EventArgs e)
		{
			Cursor.Current=Cursors.WaitCursor;
			if(m_CurrentTheme.FileName==null)
				menuFileSaveAs_Click(sender,e);
			else
				m_FileIO.SaveFile(m_CurrentTheme.FileName,m_CurrentTheme);
			Cursor.Current=Cursors.Default;
		}

		private void menuFileSaveAs_Click(object sender, System.EventArgs e)
		{
			SaveFileDialog sfd=new SaveFileDialog();
			sfd.Filter="Tetris Theme File (*.theme)|*.theme";
			if(sfd.ShowDialog()==DialogResult.OK)
			{
				Cursor.Current=Cursors.WaitCursor;
				m_CurrentTheme.FileName=sfd.FileName;
				m_FileIO.SaveFile(m_CurrentTheme.FileName,m_CurrentTheme);
				Cursor.Current=Cursors.Default;
			}
		}

		private void btnBrowse_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog ofd=new OpenFileDialog();
			ofd.Filter="PNG Image (*.png)|*.png";
			if(ofd.ShowDialog()==DialogResult.OK)
			{
				Bitmap img=new Bitmap(ofd.FileName);
				if((img.Width!=512)||(img.Height!=512))
					MessageBox.Show(this,"The background image must be a PNG image 512 pixels wide and 512 pixels high.","Wrong Format",MessageBoxButtons.OK,MessageBoxIcon.Error);
				else
					txtFileName.Text=ofd.FileName.Substring(ofd.FileName.LastIndexOf("\\")+1);
			}
		}

		private void btnViewImage_Click(object sender, System.EventArgs e)
		{
			if(m_CurrentTheme.FileName!=null)
			{
				frmPreview pre=new frmPreview();
				pre.SetPhoto(m_CurrentTheme.FileName.Substring(0,m_CurrentTheme.FileName.LastIndexOf("\\")+1)+txtFileName.Text);
				pre.ShowDialog(this);
			}
			else
			{
				MessageBox.Show("You have to save the theme before you can preview a image.");
			}
		}

		private void menuEditAddBackground_Click(object sender, System.EventArgs e)
		{
			if(!m_CurrentTheme.AddBackground(new Background("No Name")))
				MessageBox.Show(this,"You can only have 11 backgrounds in one theme.","Theme Full",MessageBoxButtons.OK,MessageBoxIcon.Error);
			else
				BuildTree();
		}

		private void menuEditRemoveBackground_Click(object sender, System.EventArgs e)
		{
			if(trvTheme.SelectedNode.Tag!=null)
			{
				m_CurrentTheme.RemoveBackground((Background)trvTheme.SelectedNode.Tag);
				BuildTree();
			}
		}

		private void menuFileNew_Click(object sender, System.EventArgs e)
		{
			m_CurrentTheme=new Theme();
			m_CurrentTheme.Name="No Name";
			BuildTree();
			EnableControls(true);
		}

		private void trvTheme_BeforeSelect(object sender, System.Windows.Forms.TreeViewCancelEventArgs e)
		{
			if((trvTheme.SelectedNode!=null)&&(trvTheme.SelectedNode.Tag!=null))
			{
				Background bg=(Background)trvTheme.SelectedNode.Tag;
				bg.Name=txtName.Text;
				bg.Artist=txtArtist.Text;
				bg.Path=txtFileName.Text;
				bg.URL=txtURL.Text;
				bg.StartLine=txtStartLine.Text;
				bg.Description=txtDescription.Text;
				m_CurrentTheme.SortBackgrounds();
				trvTheme.SelectedNode.Text=txtName.Text;
			}
			else if(trvTheme.SelectedNode!=null)
			{
				m_CurrentTheme.Name=txtAboutName.Text;
				m_CurrentTheme.Author=txtAboutAuthor.Text;
				m_CurrentTheme.Email=txtAboutEmail.Text;
				m_CurrentTheme.URL=txtAboutURL.Text;
				m_CurrentTheme.Description=txtAboutDescription.Text;
				trvTheme.SelectedNode.Text=txtAboutName.Text;
			}
		}
	}
}
