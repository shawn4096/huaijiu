// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
�������ͨ�������ǣ�����һ��С·ͨ��һ��ɽ��������һ��С�ӡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
//        "northeast" : __DIR__"outnroad1",
//        "southeast" : __DIR__"outsroad1",
		"east" : __DIR__"baihumen",
		"west" : __DIR__"tanxi",
              "south" : __DIR__"shanlu1",
                "north" : "/d/gumu/jqg/shanlu3",
	]));

   set("coor/x",-20);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

