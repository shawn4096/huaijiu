// /u/dubei/miaojiang
 

inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
��һ��ɽ·�쳣���ͣ�������ïʢ�Ĵ��֡�·�����嶾����ֲ�Ļ�ľ��ɢ��
�ų�ǵ�������
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
      if (interactive(ob) && !ob->query_temp("marks/�ⶾһ"))
//    ob->die(); 
      ob->apply_condition("man_poison",
      ob->query_condition("man_poison") + 80);
}