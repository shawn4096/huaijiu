// by dubei
// Modify By River@sj 99.5.24
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
       set("short", YEL"ɽ·"NOR);
       set("long", @LONG
����һ����᫵�ɽ·��·���ϼ�����һЩ��ɳ����ϥ��Ұ�ݼ�����·����
���ˣ���������Ұ��Ʈ�������㡣������һƬ���֣���ʱ����һ�����Ұ��
����, ͷ����һЩ��֪����С����������ȥ��
LONG
    );

       set("outdoors", "����");

       set("exits", ([
           "south" : __DIR__"xiaolu4",
           "northup" : __DIR__"xiaolu2",
       ]));

       setup();
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}


int valid_leave(object me, string dir)
{
       object *inv = deep_inventory(me);
	object *obj;

       if (dir == "south") {
           write("������һƬ�ֺ�����ʱ����һ�����Ұ�޽���, \n");
        obj = filter_array(inv,(:get_object:));        
        if (me->query("ygpass") && ! sizeof(obj))
           write("�������Ѿ���������������ָ�������Բ��ö��룬�Ų����߳����ֺ���\n");
            else {
             tell_room(environment(me), me->name()+"�������"CYN"����"NOR"�첽�뿪��\n"NOR, ({ me }));
             me->move(__DIR__"linhai" + (random(10) + 1));
             tell_room(environment(me), me->name()+"��"YEL"ɽ·"NOR"�첽���˹�����\n"NOR, ({ me }));
             return notify_fail("");
             }
        }
        return ::valid_leave(me, dir);
}
