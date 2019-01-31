#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("·��", ({ "lu zhang" }) );
	set_weight(3000);
	if( clonep() ) {
		call_out("set", 600, "no_get", 0);
		set_default_object(__FILE__);
	} else {
		set("unit", "��");
        set("long", @LONG
    ����һ��·�ϣ�ͨ�����������ٵ�ʱ����ס���������ˡ�����㲻
Ը��ð�գ����Ի�Ǯ��·(mailu)��Ҫ��û���㹻��Ǯ���Ǿ�ֻ�ܶ�·
������(duolu <����>)����������������������ٵ�������ã�Ҳ��
�����һ��(fang)��
LONG
		);
		set("value", 1000);
		set("material", "wood");
		set("no_get",1);
		set("location",1);
	}
	setup();
}

void init()
{
	object rob;
	object me=this_player();
	object ob=this_object();

	if( !ob->query("robber") ) return;
	
	if (!userp(me) || wizardp(me) || me->query("combat_exp")<100000) return;
    
	if(!objectp(rob = present(ob->query("robber"), environment(ob))) && interactive(me) ) {
		message_vision( HIC "$N���ȵء�Ŷ����һ������˭���������һ��·�ϣ��Ұ������˰ɡ���\n" NOR, me );
		call_out("remove_luzhang",0,ob );
		return;
    	}
    
    	if( me->query("g_name") == rob->query("g_name") 
    	&& me->query("g_type") == rob->query("g_type") 
    	&& me->query("id") != rob->query("id"))
    	return;

	if( userp(me) && me->query("id") != rob->query("id") 	
		&& !me->query_temp("g_robbed"))
		message_vision( HIR "$N���С������˳������ᵶ����������$nһ���󺰣�"
			+ "��·���ҿ������������ԣ���Ҫ�Ӵ˹���������·�ƣ�\n" NOR, rob,me );

	me->set_leader(0);

	add_action("do_mailu", "mailu");
	add_action("do_duolu", "duolu");
	add_action("do_fang", "fang");
	add_action("do_action", "");
}

int do_mailu( string arg )
{
	object me = this_player(), ob1,ob3,ob4,ob5;
	object ob = this_object();
	int i;

	if( me->query("id") == ob->query("robber") ) return 0;

	if(!objectp(ob1 = present(query("robber"), environment(me)))) return notify_fail( "����û���������·Ǯ���ˡ�\n" );
	if( !living(ob1) ) return notify_fail( "���" + ob1->query("name") + "������˵�ɡ�\n" );

	i = me->query("combat_exp") / 200000 + 1;
    	ob3 = present( "gold", me );
    	if(!ob3)
        	return notify_fail( "������û�лƽ�\n" );
    	if( ob3 -> query_amount() < i )
        	return notify_fail( "������û����ô��Ļƽ�\n" );

    	ob3->set_amount( ob3->query_amount() - i );
    	ob4 = present( "gold", ob1 );
    	if( !ob4 )
    	{
    	ob5 = new( "/clone/money/gold" );
		ob5->set_amount( i );
        ob5->move( ob1 );
    	}
    	else
    	{
        ob4->set_amount( ob4->query_amount() + i );
    	}
     
    	message_vision( sprintf( "$N��$nһЩ�ƽ�\n" ), me, ob1 );
	message_vision( HIC "$N��$n��ƨ���Ϻݺݵ�����һ�ţ���Ц����������"
		+ RANK_D->query_rude( me )
		+ "ʶ�࣬"
		+ RANK_D->query_self_rude( ob1 )
		+ "����ͷ���һ��\n" NOR, ob1, me );
	me->set_temp("g_robbed",1);
	ob1->add_condition("killer", 6);
	return 1;
}

int do_duolu( string arg )
{
	object me = this_player(), ob1;
	object  env = environment( me );
	mapping exits;
	object ob = this_object();

	if( me->query("id") == ob->query("robber") ) return 0;

	if( !arg || arg == "" )
		return notify_fail( "��Ҫ���ĸ������ܣ�\n" );

    	if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return notify_fail( "ֱ���߾Ϳ����ˣ����úͱ���ƴ����\n" );
    	if( !living(ob1) ) 
        	return notify_fail( "ֱ���߾Ϳ����ˣ����úͱ���ƴ����\n" );

	if( me->is_busy() )
		return notify_fail("��������æ���ء�\n");
	if( me->is_fighting() )
		return notify_fail("�㻹�ǵȴ����˼���˵�ɡ�\n");

	exits = env->query("exits");

   	if( mapp(exits) )
    	{
    	if( !exits[arg] )
    	{
    		return notify_fail( "�������û�г�·��\n" );
    		return 1;
    	}
   
	}
	
	message_vision( HIC "$N���һ������������������������ǰ��·��ȥ��\n" NOR, me );
	if( random( me->query("combat_exp") ) > ob1->query("combat_exp")/4 || random(10) < 2)
	{
		message_vision( HIC "$N��$n�������ͣ���������һ�ˣ�$n���Ƴ��˹�ȥ��\n" NOR, ob1,me);
		"/cmds/std/go" -> main( me, arg );
		return 1;
	}
	else
	{
		message_vision( HIC "$Nһ��ץס$n�������ܣ�û��ô���ס���\n" NOR, ob1,me);
		message_vision( HIR "��" + ob1->query("name")
			+ "��"
			+ RANK_D->query_self_rude( me )
			+ "�ҽ������ƴ�ˣ���\n" NOR, me );
		me->fight_ob( ob1 );
		me->start_busy(1);
		return 1;
	}
	
	return 0;
}

int do_fang( string arg )
{
	object me = this_player(), ob1;
	object ob = this_object();

	if( !ob )
		return 0;
	if( me->query("id") != ob->query("robber") )
	{
		return 0;
	}

	if( !arg || arg == "" )
		return notify_fail( "��Ҫ��˭��·��\n" );
			
    	if (!ob1 = find_living(arg)) ob1 = LOGIN_D->find_body(arg);
    	if (!ob1) 
    		return notify_fail(""+ arg + "���ڲ������\n");
        
    	if(!objectp(ob1 = present(arg, environment(me))) )
       		return notify_fail(""+ arg + "���ڲ������\n");
    	if( !living(ob1) ) 
        	return notify_fail("���" + ob1->name() + "������˵�ɡ�\n");
        
    	if( arg == me->query("id") )
    		return notify_fail( "��û��ë���ɣ�\n" );

	if( ob1->query_temp("g_robbed") )
		return notify_fail( "����˲���Ҫ����С�\n" );
		
	if( ob1->query("combat_exp") <= me->query("combat_exp") )
	{
		message_vision( HIC "$N��$n��ƨ���Ϻݺݵ�����һ�ţ���Ц����������"
			+ RANK_D->query_rude( ob1 )
			+ "���ˣ�����"
			+ RANK_D->query_self_rude( me )
			+ "����ã�����ͷ���һ��\n" NOR, me, ob1 );
		ob1->set_temp("g_robbed",1);
		return 1;
	}
	else
	{
		message_vision( HIC "$Nһ�����ŵù��ڵ��ϣ������ǻ쵰����������ǻ쵰���������\n" NOR, me );
		message_vision( HIC "��С�����۲�ʶ̩ɽ��" + ob1->query("name" ) 
			+ "�����˲���С�˹������룬���롣��\n" NOR, me, ob1 );
		message_vision( HIC "$Nî���˾�ɿ�Լ����⣬�����˵������ɿ�ң���ɿ�ײ�ɿ����\n" NOR, me, ob1 );
		message_vision( HIR "$n��žž��������ͣ�$N��ʱʹ�Ļ��˹�ȥ������\n" NOR, me,ob1 );
	    	me->unconcious();
		ob1->set_temp("g_robbed",1);
		return 1;
	}
	
	return 0;
}


int remove_luzhang( object ob )
{
	if(!ob ) 
		return 1;
		
	destruct( ob );
	return 1;
}


int do_action(string arg)
{
	object me = this_player(), ob1;
	string action = query_verb();
	mapping exits = environment()->query("exits");
	string *dir=({});
	
	if (sizeof(exits)) dir = keys(exits);
	if( member_array(action,dir) != -1 ||
		( action == "go" && member_array(arg,dir) != -1 ) )
	{
		if( me->query("id") == query("robber") )
		{
			write( "���������٣������뿪��\n");
			return 1;
		}
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;
	        
		if( me->query("combat_exp")<100000)
			return 0;	        
	    if( me->query("g_name") == ob1->query("g_name") 
	    	&& me->query("g_type") == ob1->query("g_type") )
	    	return 0;

		write( ob1->query("name") + "һ�Ѱ�����ס��С�ӣ�������·Ǯ���ߡ�\n" );
		return 1;
	}
	
	switch( action )
	{
	case "follow":
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;

		if( me->query("id") == query("robber") )
		{
			write( "���ܣ���û����ô���ס�\n" );
			return 1;
		}
		
		if( me->query("g_name") == ob1->query("g_name")
			&& me->query("g_type") == ob1->query("g_type") )
			return 0;

		write( "�㻹����Ӧ������ǰ��������˵�ɡ�\n" );
		return 1;
		break;	
	case "dazuo":
	case "tuna":
	case "respirate":
	case "exercise":
	case "practice":
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;
		if( me->query("id") == query("robber") )
			return 0;
		if( me->query("combat_exp")<100000)
			return 0;
		if( me->query("g_name") == ob1->query("g_name")
			&& me->query("g_type") == ob1->query("g_type") )
			return 0;

		write( "�㻹����Ӧ������ǰ��������˵�ɡ�\n" );
		return 1;
		break;
	}
	
	return 0;
}
