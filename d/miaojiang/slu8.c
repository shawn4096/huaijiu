// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
路势逐渐平坦，香气依旧浓郁，四周一片寂静。远处偶尔传来一两声鸟鸣，
显得异常清脆。
LONG
        );

        set("exits", ([
                "southeast" : __DIR__"slu7",
                "east" : __DIR__"slu9",
             ]));
     
        set("objects",([
//                __DIR__"npc/dushe1" : 1,

        ]));

       
        set("outdoors", "miaojiang");

        setup();
        

}
void init() 
{
      object ob=this_player();
      if (interactive(ob) && !ob->query_temp("marks/解毒一"))
//    ob->die(); 
      ob->apply_condition("man_poison",
      ob->query_condition("man_poison") + 80);
}