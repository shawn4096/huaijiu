// sjsz_room.h 

void reset()
{
	::reset();
	set("dig_times", 10 + random(20));
}

void init()
{
        object me;
        me = this_player();
        if (!me->query_condition("sjsz_time") && userp(me)){
           tell_object(me,BLINK + HIC"ͻȻ�ӱ��ϴܳ��������δ󺺣�һ�ѿ����㣬�����˳��������ʱ�����˰��졣\n"NOR);
           me->move("/d/city/chmiao");
           me->clear_condition("killer");
           me->remove_all_enemy();
           me->remove_all_killer();
           if (me->query("no_pk_recover")){
               tell_object(me,BLINK + HIG"���뿪���Խ�ɽׯ��ϵͳ�Զ��ָ�������ϴ��״̬��\n"NOR);
               me->set("no_pk",me->query("no_pk_recover"));
               me->delete("no_pk_recover");
           }
       }
}