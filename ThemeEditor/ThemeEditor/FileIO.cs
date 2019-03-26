using System;
using System.Xml.XPath;
using System.Xml;
using System.IO;
using System.Windows.Forms;
using System.Text;

namespace ThemeEditor
{
	/// <summary>
	/// Summary description for FileIO.
	/// </summary>
	public class FileIO
	{
		public FileIO()
		{

		}

		public void SaveFile(string file, Theme theme)
		{
			theme.SortBackgrounds();
			XmlTextWriter writer=new XmlTextWriter(file,Encoding.ASCII);
			writer.Indentation=1;
			writer.IndentChar='\t';
			writer.Formatting=Formatting.Indented;
			writer.WriteStartDocument();
			writer.WriteStartElement("theme");
			writer.WriteStartElement("about");
			writer.WriteElementString("name",theme.Name);
			writer.WriteElementString("author",theme.Author);
			writer.WriteElementString("email",theme.Email);
			writer.WriteElementString("url",theme.URL);
			writer.WriteElementString("description",theme.Description);
			writer.WriteEndElement();
			foreach(Background bg in theme.GetBackgrounds())
			{
				writer.WriteStartElement("background");
				writer.WriteElementString("name",bg.Name);
				writer.WriteElementString("url",bg.URL);
				writer.WriteElementString("artist",bg.Artist);
				writer.WriteElementString("description",bg.Description);
				writer.WriteElementString("path",bg.Path);
				writer.WriteElementString("start-line",bg.StartLine);
				writer.WriteEndElement();
			}
			writer.WriteEndElement();
			writer.WriteEndDocument();
			writer.Flush();
			writer.Close();
		}

		public Theme ReadFile(string file)
		{
			XPathDocument xmlDoc=new XPathDocument(file);
			XPathNavigator xmlNav=xmlDoc.CreateNavigator();
			XPathNodeIterator xmlIter=null;

			Theme theme=new Theme();
			theme.FileName=file;
			Background background=null;
			
			xmlIter=xmlNav.Select("//theme/about");
			while(xmlIter.MoveNext())
			{
				xmlIter.Current.MoveToFirstChild();
				do
				{
					switch(xmlIter.Current.Name)
					{
						case "name":
							theme.Name=xmlIter.Current.Value.Trim();
							break;
						case "author":
							theme.Author=xmlIter.Current.Value.Trim();
							break;
						case "email":
							theme.Email=xmlIter.Current.Value.Trim();
							break;
						case "url":
							theme.URL=xmlIter.Current.Value.Trim();
							break;
						case "description":
							theme.Description=xmlIter.Current.Value.Trim();
							break;
					}
				}while(xmlIter.Current.MoveToNext());
			}

			xmlIter=xmlNav.Select("//theme/background");
			while(xmlIter.MoveNext())
			{
				background=new Background();
				xmlIter.Current.MoveToFirstChild();
				do
				{
					switch(xmlIter.Current.Name)
					{
						case "name":
							background.Name=xmlIter.Current.Value.Trim();
							break;
						case "url":
							background.URL=xmlIter.Current.Value.Trim();
							break;
						case "artist":
							background.Artist=xmlIter.Current.Value.Trim();
							break;
						case "description":
							background.Description=xmlIter.Current.Value.Trim();
							break;
						case "path":
							background.Path=xmlIter.Current.Value.Trim();
							break;
						case "start-line":
							background.StartLine=xmlIter.Current.Value.Trim();
							break;
					}
				}while(xmlIter.Current.MoveToNext());
				theme.AddBackground(background);
			}
			return(theme);
		}
	}
}
