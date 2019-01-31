// /d/hmy/shiwu.c

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
ʯ�ݵ��а�����һ�޴�Ľ������̣����̵���һֻ����¨(lou)��������
���º�ľ�µ���Ҫ���ߡ�
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"pailou",
]));
	setup();
}
void init()
{
    add_action("do_yell", "yell");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"zhulou")) )
            room = load_object(__DIR__"zhulou");
        if( room = find_object(__DIR__"zhulou") ) {
            if((int)room->query("yell_trigger")==0 ) {
                room->set("yell_trigger", 1);
                set("exits/enter", __DIR__"zhulou");
                room->set("exits/out", __FILE__);
                message("vision", "һ������¨����������������ͣ�������ǰ��\n", this_object() );
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "ֻ�����������������������"
                    "�����æ���š�����\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else
        message("vision", "��¨��ͣ�������ǰ,�ֺαغ��أ�\n",
            this_object() );
}


void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "�¶��Ľ��̿�ʼת������¨���½�����ȥ��\n",
        this_object() );

    if( room = find_object(__DIR__"zhulou") )
    {
        room->delete("exits/out");
        message("vision", "�¶��Ľ��̿�ʼת������¨���½�����ȥ��\n",room);
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"zhulou") )
    {
        room->set("exits/out", __DIR__"ryping");
        message("vision", "��¨���˼��£��ڿ���ƺ��ͣ��������\n",room);

    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"zhulou") ) {
        room->delete("exits/out");
        message("vision","��¨���˼��£��ִ�ƺ��ʻ�����ϡ�\n", room);
        room->delete("yell_trigger");
    }
}

int do_yell(string arg)
{

    if( !arg || arg=="" ) return 0;

	if (arg != "����") arg = "��";
    if( (int)this_player()->query("age") < 16 )
        message_vision("$Nʹ�����̵���������һ������" + arg + "��\n",
            this_player());
    else if( (int)this_player()->query("neili") > 500 )
        message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ��"
            "�˳�ȥ��\n", this_player());
    else
        message_vision("$N������������Хһ������" + arg + "����\n",
            this_player());
    if( arg=="����")
    {
        check_trigger();
        return 1;
    }
    else
        message_vision("����ԶԶ����һ���������" + arg +
            "��������\n", this_player());
    return 1;
}



