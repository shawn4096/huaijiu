// tulu1.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long",@long
你来到了一条土路上，西南边不远好象有条江。北边是去苏州的官道。
long);
	set("outdoors", "suzhou");
	set("exits",([
		"north" : __DIR__"qsgdao5",
		"southwest" : __DIR__"tulu2",
	]));
	set("coor/x",60);
  set("coor/y",-220);
   set("coor/z",0);
   setup();
}
