// /d/xingxiu/yili2.c

inherit ROOM;
#include <ansi.h>
void quarter_pass();

void create()
{
        set("short", "伊犁城中心");
        set("long", @LONG
这儿是伊犁城中心，人来人往，十分热闹。只是都是维吾尔族人，他
们说的话你听不懂。大街小巷上，商铺林立，百货云屯，市肆繁华。西边
是一大商铺，东面则是一家财主，北边是城内最大的客栈，南面便是伊犁
城门了。
LONG
        );
        set("exits", ([ 
        	"west" : __DIR__"store",
        	"east" : __DIR__"house",
        	"northwest" : __DIR__"kezhan",
        	"south" : __DIR__"yili1",
        	"north" : __DIR__"store1",
        ]));
        set("objects", ([
                __DIR__"npc/woman": 1,
                __DIR__"npc/hman": 1,
                __DIR__"npc/wujiang": 1,
         ]));
     
        set("outdoors", "yili");

        set("coor/x",-300);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",160);
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
这儿是伊犁城中心，虽是夜晚，却还人来人往，十分热闹。只是都是
维吾尔族人，他们说的话你听不懂。大街小巷上，商铺林立，百货云屯，
市肆繁华。西边是一大商铺，东面则是一家财主，北边是城内最大的客
栈，南面的伊犁城门已经掩上。
LONG);       
        	  delete("exits/south");
                  break;
            default: set("long", @LONG
这儿是伊犁城中心，人来人往，十分热闹。只是都是维吾尔族人，他
们说的话你听不懂。大街小巷上，商铺林立，百货云屯，市肆繁华。西边
是一大商铺，东面则是一家财主，北边是城内最大的客栈，南面便是伊犁
城门了。
LONG);
                  set("exits/south", __DIR__"yili1");
        	  break;            
        }
        call_out("quarter_pass", 60);
}


