// /d/xiangyang/outnroad3.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
�����ڶ���ԥ�������·�ϣ�ż��������������ҴҶ�����������������
�����ڣ�����������Ͼ��ڡ��ϱ�ͨ�������ǣ�����Զ�������Ϻӿ��ˡ�
LONG
	);
        set("outdoors", "����");

	set("objects", ([
		__DIR__"npc/heiyi-dadao" : 1,
	]) );
	set("exits", ([
		"northwest" : __DIR__"shanxiroad1",
		"northeast" : __DIR__"henanroad1",
		"south" : __DIR__"outnroad2",
		"west" : __DIR__"hanshui1",
	]));

   set("coor/x",20);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

  
