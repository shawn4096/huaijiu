// Room: /d/fuoshan/mishi.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "����");
	set("long", @LONG
������Ƿ����ϴ�ű�������ҡ�
LONG
	);
	set("exits", ([
  "up" : __DIR__"shufang",
]));

        set("objects", ([
                __DIR__"obj/huangjingun" : 1,
                __DIR__"obj/tiancanjia" : 1,
        ]));


	setup();
}
