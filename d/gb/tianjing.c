// Room: /gaibang/xinglin.c
// by pishou

inherit ROOM;

void create()
{
    set("short", "�ﾶ");
	set("long", @LONG
��ǰ�������۶������������۵����������µ��ﾶ����һ
�����Ǽ��ʻ����������Ӹ۽��档
LONG
	);

	set("exits", ([
        "east" : "/d/suzhou/qsgdao6",
         "north" : __DIR__"xinglin1",
	]));
	set("coor/x",100);
  set("coor/y",-180);
   set("coor/z",0);
        set("outdoors", "suzhou");
   setup();
}
