int ask()
{
	object me=this_player();
	object ob2;

	if( me->query_temp("sl/pks")<3 )
		return 0;

    ob2 = new("/clone/npc/zhong-shentong");
    if( ob2 )
    {
        if( ob2->query("winner") == me->query("id"))
		{
            command( "say ��ʦ�ǵ���������������������ԡ��������֡�" );
			destruct(ob2);
			return 1;
		}
		destruct(ob2);
    }

	if( me->query("PKS")<50 )
	{
		command( "say ��ʦɱ�����أ�ֻҪ���з𷨣��Ϳ�����ȥ������" );
		me->delete_temp("sl/pks");
		return 1;
	}

	command( "say ��ʦ��ȥɱ�����࣬�����޹�����ľ�ϡ���ʯ�����졢"
		+"·�͡���������Ѫ���ӡ����֣�ʵ�ǲ���ɱ�ġ�" );
	command( "say ����ʦ����������ҵ֮�ģ����м��仰������˵����������" );
	me->start_busy(2);
	me->delete_temp("sl/pks");
	call_out("ask2",1,me);
	return 1;
}

int ask2(object me)
{
	int skill = me->query_skill("buddhism",1),
		pks = me->query("PKS");

	message_vision( HIW "������ɮ����������ļ��𣬼����ģ�����ʶ��"
		+"ʶ�����ģ����ķǷ������ġ���\n" NOR, me );
	message_vision( "$N��˼���ã��������档\n", me );
	me->set_skill("buddhism", skill-pks/20);
	me->set("PKS",pks/2);
	me->start_busy(2);
	return 1;
}
int ask_fofa()
{
object me=this_player();
if(!me->query("guilty"))
{ command("buddhi wuming");return 1;}
if(me->query_skill("buddhism",1)<200)
{ command("say ��ʦ����Ϊ���㣬�������޷��㲦���㡣");
return 1;}
if( me->query("family/master_name")!="������ɮ") return 0;
if( me->query("shen")<0) { command("say ����ȼ�թС�ˣ������ܴ���𷨣�\n");return 1;}
command("buddhi");
 message_vision( HIW "������ɮ����������ļ��𣬼����ģ�����ʶ��ʶ�����ģ����ķǷ������ġ���\n" NOR, me );
 message_vision( "$N��˼���ã��������档\n", me );
 me->start_busy(1);
me->delete("guilty");
return 1;
}
