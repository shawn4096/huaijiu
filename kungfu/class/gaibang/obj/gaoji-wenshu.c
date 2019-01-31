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

    set_name ("�漱����", ({ "wenshu" }));

    set("long", "����һ��漱����(gaoji XXX)��\n");

    if (me && present(this_object(), me)) 
    {
        add_action("do_gaoji", "gaoji");
    }
}

int do_gaoji(string str)
{
    object me = this_player(), ob = this_object();
    object ob1;
    int exp,pot,shen;
        
    if (!str || str=="")
        return notify_fail ("��Ҫ��˭�漱��\n");

    if(!objectp(ob1 = present(str, environment(me))) )
        return notify_fail("����û " + str + " ����ˡ�\n");

    if( !living(ob1) ) 
        return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");            

	if( ob1->query("name") != "�����" )
		return notify_fail("�߹ؾ���ɲ�������ʲô�˶���˵��\n");

	if(	file_name (environment(this_player())) != "/d/xingxiu/jyg" )
		return notify_fail("���������ǳ�������ģ����뿼���������顣\n");

	message_vision("$N����$nһ�Ÿ漱���顣\n",me,ob1);
	message_vision("$n��$N˵������л" 
		+ RANK_D->query_respect(me)
		+ "ǰ����Ѷ���Ҷ������Ĵ�������޻ء�\n", me, ob1 );
me->delete_temp("gb_job1");
    exp = 50 + random( 50 );
pot = exp/5+random(exp/10);
    shen = exp/2 + pot/2;
    write( sprintf(HIW "�ã���������ˣ���õ���" 
    	+ CHINESE_D->chinese_number( exp ) 
        + "��ʵս���飬" 
        + CHINESE_D->chinese_number( pot )
        + "��Ǳ�ܺ�"
        + CHINESE_D->chinese_number( shen ) 
        + "������\n" NOR));

	log_file( "job/gbjob1", sprintf("%s %s(%s) ��ؤ����ﱨ���顱���񣬵õ�%d�㾭�顣\n",
        ctime(time())[4..19], me->query("name"), me->query("id"), exp ) );

    me->add( "combat_exp", exp );
    me->add( "potential", pot );
    if( me->query("potential") > me->query("max_pot") )
    	me->set("potential", me->query("max_pot") );
    me->add( "shen", shen );

	me->apply_condition("job_busy",6);

    destruct( ob );
    return 1;
}
