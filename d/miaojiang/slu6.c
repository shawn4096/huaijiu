// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是一个小山崖，下面是深深的灌木丛。旁边有一棵大树，两名五毒教众
正在树下巡视。
LONG
        );

        set("exits", ([
            
                "southdown" : __DIR__"slu3",
                
        ]));
     
        set("objects",([
                __DIR__"npc/jiaozhong" : 2,

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