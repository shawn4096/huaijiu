//xiaolu3.c by zly

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long",
"这里是一条上山的小路，走到这里路越来越窄，听说山上经常有山
贼出没，要格外小心。没有什么事情看来还是回去吧。\n"
        );
        set("outdoors", "佛山");
        set("exits", ([
            "northeast" : __DIR__"milin",
            "southdown" : __DIR__"xiaolu2",
        ]));
//      set("objects",([
//              __DIR__"npc/yetu" : 2,
//      ]));

        set("coor/x",0);
  set("coor/y",-470);
   set("coor/z",20);
   setup();
}

