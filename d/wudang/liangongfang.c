// liangongfang.c ������ lgf.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���������������������ҵط��ż������ţ���λ�䵱��������ϥ�������������
LONG
	);
	set("exits", ([
                "east" : __DIR__"xiaolu7",
	]));
	set("objects", ([
    BINGQI_D("zhujian") : 1,
                            __DIR__"obj/mudao" : 1,
                  "/kungfu/class/wudang/chenyun" : 1,
        ]));
	
	set("coor/x",-50);
  set("coor/y",-70);
   set("coor/z",100);
   setup();
}
