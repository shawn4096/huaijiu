// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
·����ƽ̹����������Ũ��������һƬ�ž���Զ��ż������һ����������
�Ե��쳣��ࡣ
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
      if (interactive(ob) && !ob->query_temp("marks/�ⶾһ"))
//    ob->die(); 
      ob->apply_condition("man_poison",
      ob->query_condition("man_poison") + 80);
}