// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
������һ��Сɽ�£�����������Ĺ�ľ�ԡ��Ա���һ�ô����������嶾����
��������Ѳ�ӡ�
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
      if (interactive(ob) && !ob->query_temp("marks/�ⶾһ"))
//    ob->die(); 
      ob->apply_condition("man_poison",
      ob->query_condition("man_poison") + 80);
}