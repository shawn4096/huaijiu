// Room: /d/shaolin/shulin1.c
// by pishou

inherit ROOM;




void create()
{
    set("short", "杨树林");
	set("long", @LONG
这里是一片杨树林中开辟的一空地。大驿道上的一排杨树
挡住了一路尘埃和噪杂, 显得格外平静。北面是“铁面判官”
单正的大宅院, 他的五个儿子守在这儿。
LONG
	);

	set("exits", ([
        "north" : __DIR__"sjzhuang",
        "southeast" : __DIR__"yidao2",
	]));

	set("objects",([
	        __DIR__"npc/boshan" : 1,
	        __DIR__"npc/zhongshan" : 1,
	        __DIR__"npc/shushan" : 1,
	        __DIR__"npc/jishan" : 1,
	        __DIR__"npc/xiaoshan" : 1,
	]));

 	set("outdoors", "taishan");
	set("coor/x",150);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",150);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}



