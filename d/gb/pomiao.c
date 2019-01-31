// Room: /city/pomiao.c
// update by Looklove at 2000/8/25

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "������");
      set("long", @LONG
����һ���������õ������������ưܲ�����������������һ�ԣ����ϵ�
��Ҳ�����˻ҳ���һ����֪���Ѿ��ܾ�û������������ˡ����з��Ÿ����㰸��
�������ҵ����ż�����ʣ�����ļ���ͷ��Ҳ��������Ϊ���ε�ԭ��ɣ���˵ؤ
�ｭ�Ͼݵ�ͱ����ڴ˴�������ǽ�Ͽ���һ��С�š�
LONG
        );

      set("valid_startroom", 1);

      set("exits", ([
                "south" : __DIR__"xinglin9",
                "north" : __DIR__"houyuan",
      ]));

      set("objects", ([
                CLASS_D("gaibang") + "/lu" : 1,
      ]));
      setup();
        create_door("north", "����", "south", DOOR_CLOSED);
}

void reset()
{
     object ob=present("lu youjiao",this_object());
     ::reset();
     if(ob){
       ob->delete_temp("gb_job2");
       ob->delete_temp("gb_job3");
       ob->delete_temp("gb_job4");
     }
}

void init()
{       
        object me = this_player();
        int lvl,lvl1,lvl2;
        lvl = me->query_skill("bangjue", 1);
        lvl1 = me->query_skill("huntian-qigong", 1);
        if (lvl > 200 && !me->query("cut/gb")){
                lvl2 = (lvl - 200)/ 4;
                me->set_skill("bangjue", 200);
                me->set_skill("huntian-qigong", lvl1 + lvl2);
                me->set("cut/gb", lvl2 * 4);
                write(HIG "ϵͳ�ѽ�������ġ��򹷰�����ת��Ϊ��������������\n" NOR);
        }
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");
        if ((!myfam || myfam["family_name"] != "ؤ��") &&
            objectp(present("lu youjiao", environment(me))) && dir == "north")
           return notify_fail("³�нű�ȭ����û�²�Ҫ���Ű�����\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 30 &&
            objectp(present("lu youjiao", environment(me))) && dir == "north")
           return notify_fail("³�н�˵����û�±���Ű�����\n"); 

        return ::valid_leave(me, dir);
}

