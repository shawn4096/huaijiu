// /u/dubei/miaojiang
 

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这一段山路异常陡峭，两旁是茂盛的丛林。路旁有五毒教种植的花木，散发
着冲鼻的香气。
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"slu1",
                "eastup" : __DIR__"slu3",
                "northup" : __DIR__"slu4",
                
        ]));
     
        set("objects",([
                __DIR__"npc/dushe" : 1,

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