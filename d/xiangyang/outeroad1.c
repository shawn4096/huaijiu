// /d/xiangyang/outeroad1.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
����������밲�վ��ڡ�����ͨ�������ǡ�
LONG
	);
        set("outdoors", "����");

	set("objects", ([
		__DIR__"npc/duxingxia" : 1,
	]) );
	set("exits", ([
                    "east"  : "/d/city/wroad3",
              	"west" : __DIR__"qinglongmen",
//        "northwest" : __DIR__"outnroad1",
//        "southwest" : __DIR__"outsroad1",
	]));

	set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

