// Room: /gaibang/xinglin.c
// by pishou
// Modify by Looklove@SJ for update npc

inherit ROOM;

void create()
{
    set("short", "杏子林");
    set("long", @LONG
这儿是杏子林中间的一片空地。一堆丐帮帮众坐在地上商议
着帮中大事。
LONG
	);

	set("exits", ([
            "south" : __DIR__"xinglin8",
                "west" : __DIR__"kongdi2",
	     "north" : __DIR__"pomiao",
          ]));

        set("objects", ([
            __DIR__"npc/dizi3" : 1,
                CLASS_D("gaibang") + "/quan" : 1,  
                CLASS_D("gaibang") + "/xiang" : 1,  
        ]));

        set("outdoors", "suzhou");
	setup();
}
/*
int valid_leave(object me, string dir)
{
     //object *inv;
     mapping myfam;
     myfam = (mapping)me->query("family");
   if ((!myfam || myfam["family_name"] != "丐帮" ) && dir == "north") {
       //inv = all_inventory(me);
       //for(i=sizeof(inv)-1; i>=0; i--)
   if(objectp(present("chen", environment(me))))
     return notify_fail("陈长老伸手拦住你，前面是本帮禁地，请回吧。\n");       
     return 1;
}
  return 1;
}      
*/
