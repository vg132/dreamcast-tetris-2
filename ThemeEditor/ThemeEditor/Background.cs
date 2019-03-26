using System;

namespace ThemeEditor
{
	/// <summary>
	/// Summary description for Background.
	/// </summary>
	/// 

	public class Background : IComparable
	{
		private string _Name=null;
		private string _URL=null;
		private string _Artist=null;
		private string _Desc=null;
		private string _Path=null;
		private string _StartLine=null;

		public Background()
		{
		}

		public Background(string name)
		{
			_Name=name;
		}

		public int CompareTo(object obj)
		{
			if(obj is Background)
			{
				Background bg=(Background)obj;
				if((bg.StartLine!=null)&&(!bg.StartLine.Equals("")))
					return(Int32.Parse(_StartLine)-Int32.Parse(((Background)obj).StartLine));
				else
					return(-1);
			}
			throw(new ArgumentException("object is not a background"));
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

		public string Artist
		{
			get
			{
				return(_Artist);
			}
			set
			{
				_Artist=value;
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

		public string Path
		{
			get
			{
				return(_Path);
			}
			set
			{
				_Path=value;
			}
		}

		public string StartLine
		{
			get
			{
				return(_StartLine);
			}
			set
			{
				_StartLine=value;
			}
		}
	}
}