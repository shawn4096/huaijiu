// Room: /d/fuzhou/nanmen.c

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "南门");
        set("long", @LONG
这里是福州的南门，往西南方向可以通往佛山镇，可惜近日劫匪四起，民
不了生，故夜晚的吊桥放下，不准任何人等出入。现在行人还多，来来往往异
常繁忙。
LONG
        );

        set("exits", ([
                "north" : __DIR__"zhongxin",
                "south" : __DIR__"birdge",
        ]));

        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));

        set("outdoors", "福州");
        set("coor/x",100);
  set("coor/y",-480);
   set("coor/z",0);
   setup();
        quarter_pass();
}

void quarter_pass()
{
        string local;
    
        local = NATURE_D->query_daytime();
        
        switch(local){
            case "event_night":
            case "event_midnight": 
                  set("long", @LONG
这里是福州的南门，往西南方向可以通往佛山镇，可惜近日劫匪四起，民
不了生，故现在夜晚时把吊桥放下，不准任何人等出入。
LONG);       
        	  delete("exits/south");
                  break;
            default: set("long", @LONG
这里是福州的南门，往西南方向可以通往佛山镇，可惜近日劫匪四起，民
不了生，故夜晚的吊桥放下，不准任何人等出入。现在行人还多，来来往往异
常繁忙。
LONG);
                  set("exits/south", __DIR__"bridge");
        	  break;            
        }
        call_out("quarter_pass", 60);
}

int valid_leave(object me, string dir)
{
          if (dir =="south" )
        if(present("guan bing", (environment(me)))
        && me->query_condition("killer") > 0)
                return notify_fail("官兵手中的刀挡住了你的去路。\n");
        return ::valid_leave(me, dir);
}
