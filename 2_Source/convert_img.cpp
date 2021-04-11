/*
 * 	주제명(Subject): 사진 용량 변환기
 *	생성일자(Create Date): 2021-04-11 (일요일 / Sunday)
 *	파일명(FileName): convert_img.cpp 
 *	저자(Author): 도도(Dodo)
 *	라이센스(License): GNU/GPL v3 License
 *	작성언어(Programming): G++(C++ 표준)
 *	운영체제(Operation System): Ubuntu Desktop 20.04 (2021-04-11)
 *	-> 우분투(Ubuntu / Canonical Ltd), https://ubuntu.com, GNU
 *	-> CentOS(CentOS), https://www.centos.org, GNU
 *	참고도구(Reference Tools): ImageMagicK (https://imagemagick.org), GNU/GPL v3 License
 *	비고(Description):
 *	1. 최초 작성, 도도(Dodo), 2021-04-11 11:31
 *	2. 한 개 파일로 작성함, 2021-04-11 
 *	3. g++ convert_img.cpp -lpthread -o convert_img.run
 *      4. 코드 작성완료, 2021-04-11 15:26
 *
 *
 *	
 *	
 *
 */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>	// POSIX 방식
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>	// POSIX 방식

using namespace std;

const int MAX_SIZE = 100;
const char* DEFAULT_ROOT_DIR = "/home/사용자명";
const char* DEFAULT_DETAIL_DIR = "/사진/batch-convert-photo";
const char* DEFAULT_ORIGINAL_DIR = "/original";
const char* DEFAULT_CONVERT_DIR = "/convert";


class ImageToConvertor{

	private:
		int rate ;
		char* customDir ;
		
	public:
		int funcRunner( int service ) {
				
			int choose_progress_type ;
			int choose = 1;
			int usrRate ;
			int result;
			
			char* strFileName = new char[ MAX_SIZE ];
			char* strUsrDirName = new char[ MAX_SIZE ];

			string strType ;
			string strDir ;
			
			// 기본 비율
			this->setRate(40);

			while ( choose != 0){
				
		                cout << "---------------------------------";
		                cout << endl ;
		                cout << "작업하고자 하는 메뉴를 선택하세요.";
		                cout << endl ;
		                cout << "Select the menu you want to work on.";
		                cout << "---------------------------------";
		                cout << endl ;
		                cout << "1번 - 압축 비율 설정(Compression ratio setting)" ;
		                cout << endl ;
		                cout << "2번 - 경로 변경(Change path)" ;
		                cout << endl ;
		                cout << "3번 - 압축 진행(Compression progress)" ;
		                cout << endl ;
		                cout << "0번 - 돌아가기(Go Back)";
		                cout << endl ;
		                cout << "---------------------------------";
		                cout << endl ;
		                cout << "번호를 입력하세요." << endl ;
		                cout << "<<Please enter your number.>>" << endl ;

				cin >> choose;
				
				switch ( choose ) {
					
					case 1:
						cout << "비율을 입력하세요." ;
						cout << endl;
						cout << "(Enter the percentage.)" ;
						cout << endl;
						cin.clear();
						cin >> usrRate ;
						
						// 잘못된 입력
						if ( cin.fail() ){
							cout << "잘못된 입력이에요.";
							cout << endl;
							cout << "(This is an incorrect input.)";
							cout << endl;
							
							cin.ignore(256, '\n');
							cin.clear();
						}
						else{
							this->setRate ( usrRate );
						}
												
						cout << "정상적으로 입력되었습니다.";
						cout << endl;
						cout << "(It was processed normally.)";
						cout << endl;
						
						sleep(1);
						system("clear");
						
						break;
					
					case 2:
					
						cout << "사용자 경로, 파일 위치로 수정할 경우, 입력하세요.";
						cout << endl;
						cout << "(If you want to modify the ";
						cout << "user path or file location, enter it.)";
						cout << endl;
						
						cin.ignore();
						getline ( cin, strDir );
						
						strcpy(strUsrDirName, strDir.c_str() );
						// 예1: GCC => strcpy
						// 예2: VC => strcpy_s( origin, size, target);
						//strcpy_s( strFileName, 10, strTxt.c_str() );
						
						this->setCustomDir ( strUsrDirName );
						
						cout << "정상적으로 입력되었습니다.";
						cout << endl;
						cout << "(It was processed normally.)";
						cout << endl;
						
						sleep(1);
						system("clear");
						
						break;
					
						
					case 3:
						cout << "1번 - 기본경로(Default path)";
						cout << endl;
						cout << "2번 - 사용자 경로(User path)";
						cout << endl;
						
						cin.ignore();
						cin >> choose_progress_type ;
						
						strFileName = this->getProgressFileName ( choose_progress_type, strFileName );
						
						// cout << strFileName << endl ;
						
						result = this->fileToExist( strFileName );
						(result == 0)?this->fileToConvertor( strFileName ):printToFileError();
						
						sleep(5);
						system("clear");
						
						break;
				
				}
			
				
			}
			
			delete[] strFileName ;
			delete[] strUsrDirName;
			
			return 0;
		
		}
		
		char* getProgressFileName( int choose, char* usrTxt ){
			
			int result = -1;
			usrTxt[0] = '\0';	// 초기화
			
			switch ( choose ){
			
				case 1:
				 	strcat ( usrTxt, DEFAULT_ROOT_DIR );
				 	strcat ( usrTxt, DEFAULT_DETAIL_DIR );
				 	cout << usrTxt;
					break;
					
				case 2:
				 	strcpy ( usrTxt, this->getCustomDir () );
					break;
			
			}
			
			return usrTxt;
			
			
		}
		
		int printToFileError(){
				
			cout << "파일 경로 또는 폴더 경로를 확인하세요.";
			cout << endl;
			cout << "(Check the file path or folder path.)";
			cout << endl;
			return 0;		
		}
		
		int printToFileSuccess(){
				
			cout << endl;
			cout << "성공적으로 출력을 완료하였습니다.";
			cout << endl;
			cout << "(Printing has been completed successfully.)";
			cout << endl;
			return 0;		
		}		
	
		int fileToExist( char* strFilename ) {
		
			ifstream ifile ;
			ifile.open ( strFilename );
			
			if ( ifile ) {
				return 0;
			}
			else{
				return 1;
			}	
			
		}
	
		int fileToConvertor(char* strFilename){

			//DIR * dirp = opendir( strFilename );
			int restrictFile = 0;
			int index = 0;
			int rate = this->getRate();
			
			char* strName ;
			char* strOriginalDir = new char[ MAX_SIZE ] ;
			char* strConvertDir = new char[ MAX_SIZE ];
			char* strBaseCompressCmd = NULL;
			char* strArgvOriginFileCmd = new char[ MAX_SIZE ];
			char* strArgvConvertFileCmd = new char[ MAX_SIZE ];
			char* strCompressCmd = new char[ MAX_SIZE * 2 ];
			char* strMakeFolderCmd = new char[ MAX_SIZE ] ;
			
			strOriginalDir = this->getOriginalDir ( strOriginalDir, strFilename );
			strConvertDir = this->getConvertDir ( strConvertDir, strFilename );
			
			strBaseCompressCmd = this->baseCompressCmd () ;
			
			if ( fileToExist( strOriginalDir ) == 0 ){
				strMakeFolderCmd[0] = '\0';
				strcat ( strMakeFolderCmd, "mkdir -p" );
				strcat ( strMakeFolderCmd, " " );
				strcat ( strMakeFolderCmd, strOriginalDir );
				
				system ( strMakeFolderCmd );
			}
			
			if ( fileToExist( strConvertDir ) == 0 ){
				strMakeFolderCmd[0] = '\0';
				strcat ( strMakeFolderCmd, "mkdir -p" );
				strcat ( strMakeFolderCmd, " " );
				strcat ( strMakeFolderCmd, strConvertDir );
				
				system ( strMakeFolderCmd );
			}
			
			
		  	dirent * dp;
		  	DIR *dirp = opendir ( strOriginalDir ) ;
		  	
			while ( (dp = readdir(dirp)) !=NULL ) {
				
				strName = dp->d_name ;
				
				restrictFile = strcmp( strName , "." );
				restrictFile *= strcmp ( strName, "..");
				restrictFile *= strcmp( strName , "convert_img.cpp" );
				restrictFile *= strcmp ( strName, "convert_img.run" );
				restrictFile *= strcmp ( strName, "batch-target.sh" );
				restrictFile *= strcmp ( strName, "batch-resize.sh" );
				
				if ( restrictFile != 0)
				{
					strArgvOriginFileCmd = this->argvOriginFileCmd( strArgvOriginFileCmd, 
									 strOriginalDir,
									 strName );
					
					strArgvConvertFileCmd = this->argvConvertFileCmd( strArgvConvertFileCmd, 
									 strConvertDir,
									 strName );
					
					//cout << strBaseCompressCmd << " " ;
					//cout << strArgvOriginFileCmd << " " ;
					//cout << strArgvConvertFileCmd ;
					//cout << endl ;
					
					strCompressCmd[0] = '\0';
					strcat ( strCompressCmd, strBaseCompressCmd );
					strcat ( strCompressCmd, " " );
					strcat ( strCompressCmd, strArgvOriginFileCmd );
					strcat ( strCompressCmd, " " );
					strcat ( strCompressCmd, strArgvConvertFileCmd );
					
					this->printProgressCompress ( index, strCompressCmd );
					system( strCompressCmd );
					this->printCompleteCompress ( index );

				}
				
				index++;
				
		    	}
		    	
			(void)closedir(dirp);
			
			this->printToFileSuccess();
			
			//delete strName ;
			strName = NULL;
			// closedir
			delete[] strOriginalDir ;
			delete[] strConvertDir ;
			delete[] strBaseCompressCmd ;
			delete[] strArgvOriginFileCmd ;
			delete[] strArgvConvertFileCmd ;
			delete[] strCompressCmd ;
			delete[] strMakeFolderCmd;

			return 0;
		}
		
		void printProgressCompress(int index, char* cmd){
		
			cout << index << "(인덱스/index):";
			cout << cmd ;
			cout << endl ;
		}
		
		void printCompleteCompress(int index, int msg = 0){
		
			cout << "-> 변환 반응(Transformation reaction): " ;
			cout << rate ;
			cout << "%:";
			cout << "성공(Success)";
			cout << endl ;
		}
		
		char* baseCompressCmd () {

			char* strCmd = new char[ MAX_SIZE ] ;	
			std::stringstream ssInt;
			int rate = this->getRate();
			
			ssInt << rate;
			
			strCmd[0] = '\0';
			strcat ( strCmd, "convert -resize ");
			strcat ( strCmd, ssInt.str().c_str() );
			strcat ( strCmd, "%");
			
			return strCmd;
		
		}
		
		char* argvOriginFileCmd ( char* argvCmd, char* originDir, char* fileName){
					 			
			argvCmd[0] = '\0';	// 초기화
			
			strcat ( argvCmd, originDir );
			strcat ( argvCmd, "/" );
			strcat ( argvCmd, fileName );
			
			return argvCmd ;
					   
		}
		
		char* argvConvertFileCmd ( char* argvCmd, char* convertDir, char* fileName){
					 			
			argvCmd[0] = '\0';	// 초기화
			
			strcat ( argvCmd, convertDir );
			strcat ( argvCmd, "/" );
			strcat ( argvCmd, fileName );
			
			return argvCmd ;
					   
		}
		
		char* getOriginalDir( char* usrDir, char* homeDir ){
			
			usrDir[0] = '\0';	// 초기화
			strcat ( usrDir, homeDir );
			strcat ( usrDir, DEFAULT_ORIGINAL_DIR );
			
			return usrDir;
		}
		
		char* getConvertDir( char* usrDir, char* homeDir ){
			
			usrDir[0] = '\0';	// 초기화
			strcat ( usrDir, homeDir );
			strcat ( usrDir, DEFAULT_CONVERT_DIR );
			
			return usrDir;
		}
		
		void posixfileDir( char *strFileName ){
		
			DIR * dirp = opendir( strFileName );
		  	dirent * dp;
		  	
			while ( (dp = readdir(dirp)) !=NULL ) {
				cout << dp->d_name << " size " << dp->d_reclen<<std::endl;
		    	}
		    	
			(void)closedir(dirp);
		}
		
		int getRate() const{
			return this->rate;
		}
		
		void setRate(int rate) {
			this->rate = rate;		
		}
		
		char* getCustomDir () const {
			return this->customDir;
		}
		
		void setCustomDir ( char* usrDir ) {
			this->customDir = usrDir ;		
		}
	
	protected:

	
};

class MagicMain{

        private:


        public:
                void run(){

			ImageToConvertor* convertor = new ImageToConvertor();
                        int choose = 1;
                        int msg = -1;

                        while ( choose != 0 ){

                                cout << "---------------------------------";
                                cout << endl ;
                                cout << "ImageMagicK로 변환 (압축)";
                                cout << "(Convert To ImageMagicK(compress))";
                                cout << endl ;
                                cout << "최초 빌드: 2021-04-11 15:24 [일요일]" << endl;
				 cout << "First build: 2021-04-11 15:24 [Sunday]" << endl;
                                cout << "버전(Version): 0.01" << endl;
                                cout << "---------------------------------";
                                cout << endl ;
                                cout << "작업하고자 하는 메뉴를 선택하세요.";
                                cout << endl ;
                                cout << "Select the menu you want to work on.";
                                cout << "---------------------------------";
                                cout << endl ;
                                cout << "1번 - 센토스 (CentOS) DNF - ImageMagicK 설치" ;
                                cout << endl ;
                                cout << "2번 - 우분투 (Ubuntu) apt - ImageMagicK 설치";
                                cout << endl ;
                                cout << "3번 - 센토스 (CentOS) YUM - ImageMagicK 설치" ;
                                cout << endl ;
                                cout << "4번 - 사진 압축(Photo compression)";
                                cout << endl ;
                                cout << "5번 - 도움말(Help)";
                                cout << endl ;
                                cout << "0번 - 종료(Exit)";
                                cout << endl ;
                                cout << "---------------------------------";
                                cout << endl ;
                                cout << "번호를 입력하세요." << endl;
                                cout << "(Please enter your number.)" << endl ;

				cin >> choose;
				
				switch ( choose ){
				
					case 1:
						system("sudo dnf install -y imagemagick");
						cout << "정상적으로 처리되었습니다.";
						cout << endl;
						cout << "(It was processed normally.)";
						cout << endl;
						
						sleep(2);
						
						break;
						
					case 2:
						system("sudo apt-get -y install imagemagick");
														
						cout << "정상적으로 처리되었습니다.";
						cout << endl;
						cout << "(It was processed normally.)";
						cout << endl;
						
						sleep(2);
						
						break;
				
					case 3:
						system("sudo yum install -y imagemagick");
						cout << "정상적으로 처리되었습니다.";
						cout << endl;
						cout << "(It was processed normally.)";
						cout << endl;
						
						sleep(2);
						break;
						
					case 4:			
						msg = convertor->funcRunner( choose );
						break;
						sleep(2);
						
					case 5:
						cout << "------------------------------------------------" << endl;
						cout << "5번 - 도움(Help)" ;
						cout << endl ;
						cout << "------------------------------------------------" << endl;
						cout << "컴파일 방법(How to compile)" << endl ;
						cout << "g++ convert_img.cpp -lpthread -o convert_img.run";
						cout << endl << endl;
						cout << "라이센스(License): GNU/GPL v3 License" << endl ;
						cout << "운영체제(Operation System): " << endl;
						cout << "--> 1. Ubuntu(우분투) - (https://ubuntu.com), GNU" << endl ;
						cout << "--> 2. CentOS(센토스) - (https://www.centos.org), GNU" << endl ;
						cout << endl ;
						cout << "------------------------------------------------" << endl;
						cout << "라이브러리(Library)" << endl ;
						cout << "--> 1. ImageMagicK(https://imagemagick.org), 1999~, GNU/GPL v3 License" << endl ;
						sleep(5);
				
				};
				
				system("clear");

                        }
                        
                   delete[] convertor ;


                }


        protected:



};



void* thread_convertor(void *arg) {

	MagicMain* app = new MagicMain();
	app->run();

	delete[] app;

	return NULL;

}

int main(){

	pthread_t thread;
	pthread_create(&thread, NULL, thread_convertor, NULL ) ;

	pthread_join(thread, NULL);

	return 0;
}
