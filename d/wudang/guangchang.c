// Room : /d/wudang/guangchang.c  �䵱�㳡
// by ydh
#include <ansi.h>
inherit ROOM;
int do_zhao(string arg);

void create()
{
        set("short",HIW"�䵱�㳡"NOR);
        set("long", @LONG
����һ���ɴ��ʯ���̳ɵĹ㳡�����������������ܣ�ʮ������
������ȫ��ǽ�ǻ�ɢ���ż���������ʯ����һЩ������䵱����ѧ
ϰ�书�ͻ����д�ĵص㡣��Χ��������ͩ����һ������������ص�
��Ҷ��һ���������ĵ�ͯ���ڴ�ɨ���ϱ�������������
LONG                           
        );
	set("outdoors", "�䵱");
        set("exits", ([
		   "south" : __DIR__"sanqingdian",
                "northdown" :__DIR__"zxgdamen",
        ]));

        set("objects",([
                "/kungfu/class/wudang/guxu" : 1,
                __DIR__"npc/daotong" : 2,

        ]));

        set("coor/x",-20);
  set("coor/y",-60);
   set("coor/z",100);
   setup();
}

void init()
{
        add_action("do_zhao", ({"zhao","find"}));
}

int do_zhao(string arg)
{
              mapping fam; 
        object me,yc;
        me=this_player();
              fam = me->query("family");

        if ( arg != "yao chu" )
            return notify_fail("��Ҫ��ʲô��\n");
              
                if (!fam || fam["family_name"] != "�䵱��")
                      return notify_fail("���ֲ����䵱���ӣ��ܵ��䵱��Ϲ��ʲ�ᶫ������\n");

    if (me->query_temp("yaochu_get"))
            return notify_fail("��ô��ô̰�������ù�һ������\n");         
 
              if (me->query("combat_exp",1) <= 20000)
                     return notify_fail("������䵱��ҪϹ��������\n");
         yc=unew("/d/wudang/obj/yaochu");
       if (yc)
          {
           message_vision("$N��ǽ�ŵ�������﷭����ȥ�ҳ�һ��ҩ����\n", me);
          me->set_temp("yaochu_get",1);
           yc->move(me);}
        else
           message_vision("$N��ǽ�ŵ�������﷭����ȥʲôҲû���š�\n", me);
     return 1;
}
