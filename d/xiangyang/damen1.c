// Room: damen.c

inherit ROOM;

void create()
{
        set("short", "大门");
        set("long", @LONG
你走到一座高宅大院的门口，大门紧闭，门口站着几个家丁，一个个腆胸叠肚，
一副要找人麻烦的样子。门前左右有两个石狮子，四五级青石台阶上是两扇钉满铜
钉的大门。看得出这里是当地大豪的住所。
LONG
        );
         

        set("objects", ([
                __DIR__"npc/jiading":2,
        ]));
        
        set("exits", ([
                "south": __DIR__"shide",
                "north": __DIR__"xiaoxiang1",
        ]) );

        set("coor/x",-10);
 set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

