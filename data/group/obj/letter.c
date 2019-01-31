// ����� code ѡ���Ƿ�������

#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
    set("unit","��");
    set("no_get", 1);
    set("no_drop", 1);
    set("no_put", 1);
    set("no_give", 1);
    set("material", "paper");
    set_weight(1);
    setup();
}

void init()
{
    object me = this_player();
    if (!me->query_temp("g_name") )
    {
	    set_name (HIR"������"NOR, ({ "invite letter","letter"}));
        set("long", "����һ�������š�Ը������ gjoin <������id> ����Ը�������Ծܾ� gjoin cancel��\n");
    }
    else
    {
        set_name (HIR + me->query_temp("g_name") + me->query_temp("g_type")
        	+ "������"NOR, ({ "invite letter","letter" }));
        set("long", "����һ������"HIG + me->query_temp("g_name") + me->query_temp("g_type")
            + NOR "�������ţ�����д����\n"
            + me->query("name") + RANK_D->query_respect(me) + "��\n"
            + "    " + me->query_temp("g_name") + me->query_temp("g_type") + "����"
            + RANK_D->query_respect(me) + "���ˡ�\n    ��" + me->query_temp("g_type")
            + "��ּ��" + me->query_temp("g_idea")
            + "��\n                         " + me->query("g_invite_name")
            + "\nԸ������ gjoin <������id> ����Ը�������Ծܾ� gjoin cancel��\n");
    }
    if (me && present(this_object(), me))
        add_action("do_agree", "gjoin");
}

int do_agree(string str)
{
    object ob1, me = this_player();
    string st1;

    if (!str || str=="") return notify_fail ("��Ҫ����˭�����룿\n");

    if ( str=="cancel")
    {
	    message_vision("$N�ܾ������룬������ʱ�����������֯��\n",me);
        message_vision("$N͵͵�İ��������ӵ��ˡ�\n",me);
        me->delete_temp("g_level");
        me->delete_temp("g_name");
        me->delete_temp("g_type");
        me->delete_temp("g_header_name");
        me->delete_temp("g_idea");
        me->delete_temp("g_number");
        me->delete("g_invite_name");
        me->delete("g_invite_id");
        destruct(this_object() );
        return 1;
    }

    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (!ob1) return notify_fail(""+ str + "���ڲ������\n");

    if(!objectp(ob1 = present(str, environment(me))) )
        return notify_fail(""+ str + "���ڲ������\n");
    if ( str != me->query("g_invite_id") )
        return notify_fail("���� "+ str + " �����������ġ�\n");
    if( !living(ob1) )
        return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
    else
    {
        me->set("g_level",me->query_temp("g_level"));
        me->set("g_name",me->query_temp("g_name"));
        me->set("g_type",me->query_temp("g_type"));
        me->set("g_idea",me->query_temp("g_idea"));
        me->set("g_number",me->query_temp("g_number"));
        st1 = me->query_temp("g_header_name");
        me->set("g_header_name",st1);
        me->set("old_title",me->query("title"));
        switch((int)me->query_temp("g_level"))
        {
        case 2:
        	me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"��"+ me->query("g_type") +"��"NOR);
            break;
        case 3:
        	me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
            break;
        case 4:
        	me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"ʹ��"NOR);
            break;
        case 5:
        	me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
            break;
        default:
        	me->set("title","��"HIW+ me->query("g_name") + me->query("g_type") + NOR "��"+ HIG +"����"NOR);
        }
        me->set("new_title",me->query("title") );
        new("/data/group/obj/ling")->move(me);
        message_vision("$n������$N�����룬�����ˣ�" HIW+ me->query("g_name") + me->query("g_type") + NOR"�ݡ�\n",ob1,this_player() );
        message_vision("$n����$Nһ����" HIW+ me->query("g_name") + me->query("g_type") + NOR"������ ��\n",this_player(),ob1 );
        me->delete_temp("g_level");
        me->delete_temp("g_name");
        me->delete_temp("g_type");
        me->delete_temp("g_header_name");
        destruct(this_object() );
        return 1;
    }
}
