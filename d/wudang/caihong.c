// /d/wudang/caihong.c 彩虹(石梁)
// by ydh and shang

inherit ROOM;

void create()
{
        set("short", "雨后彩虹");
        set("long", @LONG
你走入山坞中，这里是九渡涧的下流，各岭之水均在此交汇，然
后突然倾泻而下注入山涧形成壮观的瀑布。一条天然石梁横跨两岸，
远处观看在是一条雨后彩虹。再往上就是陡峭的十八盘了。
LONG
        );

        set("exits", ([
                "southup" : __DIR__"shibapan",
 "northup" : __DIR__"wangbeipo",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,

        ]));

        set("no_clean_up", 0);
        set("outdoors", "wudang");

        set("coor/x",0);
  set("coor/y",-30);
   set("coor/z",50);
   setup();
}
