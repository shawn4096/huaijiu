// /d/xiangyang/hunanroad2.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����������������·�ϣ�ż��������������ҴҶ����������Ѿ��Ǻ���
�ؽ磬����������������ڡ��ϱ���һ��С��
LONG
	);
        set("outdoors", "����");

	set("objects", ([
		__DIR__"npc/dujiao-dadao" : 1,
	]) );
	set("exits", ([
		"northeast" : __DIR__"hunanroad1",
		"southwest" : "/d/dali/shanlu1",
		"south" : "/d/tiezhang/lx",
	]));

	set("coor/x",-290);
  set("coor/y",-280);
   set("coor/z",-20);
   setup();
}

