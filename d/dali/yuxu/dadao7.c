// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "���");
	set("long", @LONG
���ڴ���ϣ����߶���������������·���������˲����ࡣ����͵��Ĵ�
�����ˡ�
LONG
	);
        set("outdoors", "����");
	set("exits", ([ 
            "north" : "/d/chengdu/eroad2",
	    "south" : __DIR__"dadao6",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-80);
  set("coor/y",-30);
   set("coor/z",0);
   setup();
}
