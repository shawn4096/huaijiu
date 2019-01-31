// gate.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "���Ź�" NOR);
        set("long", "�������������������ڡ����Źء���������ǰ������һ���ߴ��
��ɫ��¥������������޿�������ж�ǰ������Ϊһ�����Źؾ��޷���
�������ˡ�\n");
        set("exits", ([
                "enter" : __DIR__"gateway",
        ]) );
        set("no_fight", 1);
        setup();
}

void init()
{
        object me = this_player();
        if(me->query("thd/qiankun")) //�һ���Ǭ��һָ
        {
                 me->set("max_qi",me->query("qiankun/qi"));
                 me->set("max_neili",me->query("qiankun/neili"));
                 me->delete("qiankun/qi");
                 me->delete("qiankun/neili");
        }
        if (me->query("thd/fugu")) // �һ������Ƕ�
                 me->delete("thd/fugu");
        if(me->query("dec/str")) { //�������߳�ɢ
            me->add("str",me->query("dec/str"));
            me->delete("dec/str");
        }
        if (me->query("duanzhi")) //��������ָ
                 me->delete("duanzhi");
        if (me->is_ghost())
                call_out( "run", 1, me);
}

void run(object ob)
{
        if (!ob || !present(ob)) return;
        tell_object(ob, HIW"һ�������Ũ��ͻȻ���֣��ܿ�ذ�Χ���㡣\n\n"NOR);

        if (ob->query("class") == "bonze" || ob->query("class") == "lama")
                ob->move(__DIR__"pusadian"); 
        else
                random(2)?ob->move(__DIR__"gateway"):ob->move(__DIR__"mpting");
}

int valid_leave(object me, string dir)
{
        if( wizardp(me) || !userp(me) ) return ::valid_leave(me, dir);
        if( dir == "enter") 
                return notify_fail(
"�ռ�������ǰ������Ϊ����ǧ���ڲ������˽����Χ��ʹ�㶯�����ã���
Щ��������Ů������������¥�����ϵļ��������ѿ��ڵò������Σ�����
��һȺƤ���Źǵ����ã��൱���ˣ�\n"
                );
        return ::valid_leave(me, dir);
}

