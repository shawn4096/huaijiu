
inherit ROOM;

void create()
{
	set("short", "��̳���");
	set("long", @LONG
  �����ǵ������������̳����ڣ����Ե���������ɵ���̳��
LONG
	);

	set("exits", ([
		"south" : "/d/city/wroad3",
	]));

	set("inited",0);
	setup();
}

void init()
{
	int line = 1;
	string dir,file;
	string s_log;
	
	//����log�ļ���̬���ó���
	if( !query("inited") )
	{
        while( s_log = read_file(__DIR__"/groom/log",line,1) )
        {
if(sscanf(s_log,"������̳ %s ���� %s",file,dir)==2)
            {
set("exits/"+dir[0..strlen(dir)-2],file);
            }
            line ++;
        }
        
        set("inited",1);
	}
}
