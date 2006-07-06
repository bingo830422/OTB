/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbSystem.h"
#include <string.h> // strdup


#if defined(WIN32) || defined(WIN32CE)
/*=====================================================================
                   WIN32 / MSVC++ implementation
 *====================================================================*/
        #ifndef WIN32CE
                #  include <io.h>
        #else
                #  include <wce_io.h>
        #endif
#else
/*=====================================================================
                      POSIX (Unix) implementation
 *====================================================================*/
        #include <sys/types.h>
        #include <dirent.h>
#endif


namespace otb
{


//GetExtension from uiig library.
std::string
System::GetExtension( const std::string& filename )
{

  // This assumes that the final '.' in a file name is the delimiter
  // for the file's extension type
  const std::string::size_type it = filename.find_last_of( "." );

  // This determines the file's type by creating a new string
  // who's value is the extension of the input filename
  // eg. "myimage.gif" has an extension of "gif"
  std::string fileExt( filename, it+1, filename.length() );

  return( fileExt );
}

//GetRootName from uiig library.
std::string
System::GetRootName( const std::string& filename )
{
  const std::string fileExt = GetExtension(filename);

  // Create a base filename
  // i.e Image.ent --> Image
  if( fileExt.length() > 0 )
    {
    const std::string::size_type it = filename.find_last_of( fileExt );
    std::string baseName( filename, 0, it-fileExt.length() );
    return( baseName );
    }
  //Default to return same as input when the extension is nothing (Analyze)
  return( filename );
}


#if defined(WIN32) || defined(WIN32CE)

/*=====================================================================
                   WIN32 / MSVC++ implementation
 *====================================================================*/

std::vector<std::string> System::Readdir(std::string pszPath)
{
    struct _finddata_t c_file;
    long    hFile;
    std::vector<std::string>  listFileFind;
    std::string  pszFileSpec;
    std::string path(pszPath);
    
    if (pszPath.empty() == true)
        path = ".";

    pszFileSpec = path + "\\*.*";

    if ( (hFile = _findfirst( pszFileSpec.c_str(), &c_file )) != -1L )
    {
        do
        {
            listFileFind.push_back(c_file.name);
        } while( _findnext( hFile, &c_file ) == 0 );

        _findclose( hFile );
    }

    return listFileFind;
}

#else

/*=====================================================================
                      POSIX (Unix) implementation
 *====================================================================*/

/**
 * Read names in a directory.
 *
 * This function abstracts access to directory contains.  It returns a
 * list of strings containing the names of files, and directories in this
 * directory.  The resulting string list becomes the responsibility of the
 * application and should be freed with CSLDestroy() when no longer needed.
 *
 * Note that no error is issued via CPLError() if the directory path is
 * invalid, though NULL is returned.
 *
 * @param pszPath the relative, or absolute path of a directory to read.
 * @return The list of entries in the directory, or NULL if the directory
 * doesn't exist.
 */

std::vector<std::string> System::Readdir(std::string pszPath)
{
    DIR           *hDir;
    std::vector<std::string>  listFileFind;
    struct dirent *psDirEntry;
    std::string path(pszPath);
    
    if (pszPath.empty() == true)
        path = ".";

    if ( (hDir = opendir(path.c_str())) != NULL )
    {
        while( (psDirEntry = readdir(hDir)) != NULL )
        {
            listFileFind.push_back(psDirEntry->d_name);
        }

        closedir( hDir );
    }
    return listFileFind;
}

#endif


}
