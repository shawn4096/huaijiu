// Room: 大道 3
// bbb 1997/06/11
// Modify By River 98/12 
inherit ROOM;

void create()
{
        set("short", "大道");
	set("long", @LONG
一条笔直的石板大道通向前方，路上不时的有南来北往的车马经过，到了
这里你发现穿民族服饰的人越来越多了，大理居民中有三分之一为少数民族，
有彝、白、哈尼、傣等二十多个民族，路旁的茶花笑脸迎人。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 1 */
          "northeast" : __DIR__"htq",
	  "north" : __DIR__"dadao2",
	  "south" : __DIR__"dadao4",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-310);
  set("coor/y",-350);
   set("coor/z",-20);
   set("coor/x",-310);
  set("coor/y",-350);
   set("coor/z",-20);
   setup();
}
