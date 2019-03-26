using System;
using System.Collections;

namespace ThemeEditor
{
	/// <summary>
	/// Summary description for Theme.
	/// </summary>
	public class Theme
	{
		private string _Name=null;
		private string _Author=null;
		private string _Email=null;
		private string _URL=null;
		private string _Desc=null;
		private string _FileName=null;
		private ArrayList Backgrounds=new ArrayList();

		public Theme()
		{
		}

		public bool AddBackground(Background background)
		{
			if((background!=null)&&(Backgrounds.Count<11))
			{
				Backgrounds.Add(background);
				SortBackgrounds();
				return(true);
			}
			return(false);
		}

		public void SortBackgrounds()
		{
			Backgrounds.Sort();
		}

		public void RemoveBackground(Background background)
		{
			Backgrounds.Remove(background);
		}

		public Background GetBackground(int pos)
		{
			return((Background)Backgrounds[pos]);
		}

		public ArrayList GetBackgrounds()
		{
			return(Backgrounds);
		}

		public Background GetBackgroundByName(string name)
		{
			foreach(Background background in Backgrounds)
			{
				if(background.Name.Equals(name))
					return(background);
			}
			return(null);
		}

		public string FileName
		{
			get
			{
				return(_FileName);
			}
			set
			{
				_FileName=value;
			}
		}

		public string Name
		{
			get
			{
				return(_Name);
			}
			set
			{
				_Name=value;
			}
		}

		public string Author
		{
			get
			{
				return(_Author);
			}
			set
			{
				_Author=value;
			}
		}

		public string Email
		{
			get
			{
				return(_Email);
			}
			set
			{
				_Email=value;
			}
		}

		public string URL
		{
			get
			{
				return(_URL);
			}
			set
			{
				_URL=value;
			}
		}

		public string Description
		{
			get
			{
				return(_Desc);
			}
			set
			{
				_Desc=value;
			}
		}
	}
}
