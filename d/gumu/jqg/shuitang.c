// shuitang.c ˮ��
// By River 99.5.25
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
           set("short","ˮ��");
	   set("long",@LONG
�������֣�ͻȻһ������ӿ������ǰ�ޱ��޼ʵ�ȫ��ˮ�ɻ���ԭ��������
ǳǳ��һƬˮ�������ߣ�������ˮ�ɣ��⻨��ԭ���Ϸ�֮���֪���Ծ�
���ڹ���֮���ɽ�����֡�
LONG
);

           set("outdoors","�����");
	   set("exits",([
              "eastup": __DIR__"shanding",
              "westdown": __DIR__"qsroad",
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

       if (dir == "eastup") {
           write("������һ��Ƭ���֣��������ټ��������ï�ܵ����֣�����֮��ȷʵ������\n");
        obj = filter_array(inv,(:get_object:));        
        if ( random(me->query("kar")) > 12 && ! sizeof(obj))
           write(HIW"\n�㻺�����������д������ŵ�һ���󵭵����㣬�Ǿ����׾�����\n\n"NOR);
            else {
             tell_room(environment(me), me->name()+"�����ߵ�"GRN"����"NOR"�첽�뿪��\n"NOR, ({ me }));
             me->move(__DIR__"zhulin" + (random(6) + 1));
             tell_room(environment(me), me->name()+"��ˮ���첽���˹�����\n"NOR, ({ me }));
             me->look();
             return notify_fail("");
             }
        }
        return ::valid_leave(me, dir);
}
