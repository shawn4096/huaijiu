#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ɽ·");
        set("long", @LONG
һ����������̤����С�������������������������ɽ����չ�����Ե���
��(grass) �ߴ���ߣ���ס����⡣ɽ���е�һ�ж��Ե���ɭ�İ�������ʹ��
�ֲ���ǰ���ĵ�·��
LONG                           
        );

        set("exits", ([
                "southeast" : __DIR__"slu1",
        ]));
        set("item_desc", ([
                "grass": "�����Ӳ�(grass)���ܣ������ƺ����Բ���(push)���ǡ�\n",
                "�Ӳ�": "������Ӳ�(grass)���ܣ������ƺ����Բ���(push)���ǡ�\n"
        ]));
        setup();
}
void init()
{
        add_action("do_push", "push");
}
int do_push(string arg)
{
        if( arg == "grass" || arg == "é��" || arg == "��")
        {
        message_vision("$N����·�ߵ��Ӳݣ�������һ����������·��\n", this_player());
        if( !query("exits/northwest") ) {
        set("exits/northwest", __DIR__"houshan");
        call_out("close_path", 5);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/northwest") ) return;
        message("vision",
"һ��紵�����Ӳݻ��˻Σ�����û����������·��\n",
                this_object() );
                delete("exits/northwest");
}
