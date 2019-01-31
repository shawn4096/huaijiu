#include <ansi.h>

int exercising(object me);
int halt_exercise(object me);
int find(string arg, object me);

int exert(object me, mixed arg)
{
      if(!arg)
          return notify_fail("��ʽ��exert shentong <id> \n"); 
      
      if(objectp(arg))
          return notify_fail("��Ҫ�ҵ��˾���һ�ԣ�������ͨ����ʲô��\n"); 
          
      if(!stringp(arg))
          return notify_fail("��Ҫ����ͨ��ʲô��\n"); 
          
      if(arg==me->query("id"))
          return notify_fail("����ͨ���Լ����㲻���߻���ħ�˰ɣ�\n"); 
          
      if( (int)me->query_skill("longxiang-gong",1) < 150 )
          return notify_fail("�������������������ȣ��޷����á���ͨ����\n"); 
          
      if( (int)me->query_skill("lamaism",1) < 150 )
          return notify_fail("��������ķ��������޷����á���ͨ����\n");    
            
      if( me->is_fighting() )
          return notify_fail("����ͨ��ֻ���ڰ����Ļ�����ʹ�á�\n");
          
      if( (int)me->query("neili") < 500 || (int)me->query("max_neili")<2000  ) 
          return notify_fail("�������������\n");
          
      if( (int)me->query_temp("mz_shenyou") ) 
          return notify_fail("���Ѿ����������ڴ����ˡ�\n");
          
      if( me->query("jing") < me->query("eff_jing"))        
          return notify_fail("�㾫����������ܡ���ͨ����\n");  
          
      if( me->query("jingli") < 800)
          return notify_fail("��Ŀǰ����˥�ߣ������޷�����ͨ����\n");
          
      if( me->query_int() < 32)
          return notify_fail("ֻ�д��Ǵ��֮�˲���ͨ������ͨ�������������ǲ��е��ˡ�\n");
          
      me->add("neili", -300);

      message_vision(HIW"\n$N��ϥ��Ŀ�����б��д�˷𾭣����������������䡣���������ٴ죬�����з����������ɣ���ʼ���롸���Ρ����硣\n\n" NOR, me);

      me->set_temp("mz_shenyou", 1);
      me->set_temp("period", 1);
      me->set_temp("person", arg);
      me->start_busy((: exercising :), (:halt_exercise:));
      return 1;
}

int exercising(object me)
{
	int period = (int)me->query_temp("period");

	me->receive_damage("jing", 5+random(2));
	me->receive_damage("jingli", 5+random(2));

        if(!living(me)) return 0;
        if(me->query("jing") < 1 || me->query("jingli") < 1){
        	me->delete_temp("mz_shenyou");
        	me->delete_temp("period");
        	me->delete_temp("person");
        	me->unconcious();
        	return 0;
        }
        if(!me->query_temp("person")){
        	 halt_exercise(me);
        	 return 0;
        	 }
	switch(period) {
        case 3:
                write("\n��ȫ����ɣ������������ڼ꣬����������\n\n");
                break;
        case 8:
                write("\n��һ�����������Լ�����־Խ��Խ���ѣ�������ҲԽ��Խ���ˡ�\n\n");
                break;
        case 13:
                write(HIY"\n�����أ��㷢���㿴�����Լ���ϥ����������������Ѿ��ֿ����Ƶġ�\n\n"NOR);
                break;
        case 18:
                write(HIC"\n�㷢���Լ�����־Խ��ԽԶ����˲ʱ���Ѿ�����˸�ɽ�󺣣��ε������֮�У�\n\n"NOR);
                me->improve_skill("force", 1);
                break;
        case 23:
                write(HIW"\n���˼�����ſ�ȥ��ֻһɲ�ǣ��㿴�������뿴�Ķ�����\n\n"NOR);
                find(me->query_temp("person"), me);
                me->add("combat_exp", 1);
                break;
        case 28:
                write("\n�����أ����˼���ֻ�ת������һ˿��΢����������������Ҳ��ʼ���˸о���\n\n");
                me->add("potential", 1+random(5));
                break;
        case 30:
                write("\n�㻺��վ��������ֻ����ȫ�����ѣ�ʮ��ƣ����\n\n");
                tell_room(environment(me), me->name()+"��������һ�ڻ���������վ��������\n\n", ({ me }));
                me->set("jing", 1);
                me->set("jingli", 1);
                me->delete_temp("period");
                me->delete_temp("person");
                me->delete_temp("mz_shenyou");
                me->start_busy(2);
                return 0;
                break;
        }
        period++;
        me->set_temp("period", period);
        return 1; 
}

int halt_exercise(object me)
{
	me->delete_temp("mz_shenyou");
	me->delete_temp("period");
	me->delete_temp("person");
	me->receive_damage("jing", 50);
	me->receive_damage("jingli", 50);
	write("����ͷһ����ң��ٲ��ܾ����붨��ֻ������վ��\n");
        tell_room(environment(me), me->name()+"ȫ��һ�󶶶������ź���һ������������վ��������\n", ({ me }));
        me->start_busy(1+random(5));
	return 1;
}

int find(string arg, object me)
{
        object where, target;

        if (!geteuid()) seteuid(getuid());
        target = LOGIN_D->find_body(arg);
        if (!target) target = find_living(arg);
	if (!target) {
		tell_object(me, YEL"\n����ϸ���˰��죬ȴ������ֻ�Ǹ���Ӱ������Ȼ��֪��������...\n\n"NOR);
		return 1;
		}
	if (wizardp(target)){
		tell_object(me, MAG"\n���Ȼ���֣����˾��Ǻ������֣�����һ��Ư���ڰ�յ���
���һ��ع�ͷ����������һ�ۣ���е����²����æ���˻�����\n\n"NOR);
                return 1;
                }
	where = environment(target);
	if (!where) {
		tell_object(me, HIB"\n����ڤڤ�ие�������˵Ĵ��ڣ���ȴ���������Ҳ����������ڣ�
�����������ǵ���һ����Ϊ������֪�ĵط���ֻ������֪���ĵط���\n\n"NOR);
                return 1;
                }
	"/cmds/std/look"->look_room(me, where);
        tell_object(me, HIW"\n\n�����ֻ��һ�������˼���������˻����ˡ�\n"NOR);
        return 1;
}

