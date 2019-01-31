// study.c

#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        object ob;
        string zhao_name, str;
        mapping skill;
        int my_skill, cost, num;

        if (where->query("pigging"))
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");
        if (where->query("no_fight"))
                return notify_fail("���ﲻ�ܶ��飡\n");
        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (where->query("sleep_room"))
                return notify_fail("���Ҳ��ܶ��飬��Ӱ�������Ϣ��\n");

        if( me->is_fighting() )
                return notify_fail("���޷���ս����ר�������ж���֪��\n");

        if(!arg)
                return notify_fail("��Ҫ��ʲô��\n");

        sscanf(arg, "%s %d", arg, num);
        
        if(!objectp(ob = present(arg, me)))
                return notify_fail("��Ҫ��ʲô��\n");
                
        if( !mapp(skill = ob->query("skill")) )
                return notify_fail("���޷�����������ѧ���κζ�����\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

        if (!random(5))
                message("vision", me->name() + "��ר�ĵ��ж�" + ob->name()
                + "��\n", environment(me), me);

        if( (int)me->query("combat_exp") < skill["exp_required"])
                return notify_fail("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
               
        if( me->query_int() < skill["difficulty"])
              return notify_fail("����Ŀǰ��������������û�а취ѧ������ܡ�\n");

        notify_fail("����Ŀǰ����������û�а취ѧ������ܡ�\n");
        if( !SKILL_D(skill["name"])->valid_learn(me) ) return 0;

        cost = skill["jing_cost"] + skill["jing_cost"] 
                * (skill["difficulty"] - (int)me->query("int"))/20;
        if (cost < 10) cost = 10; // minimum cost
	if (num > me->query("jing")/cost) num = me->query("jing")/cost;
       
        if( num ){
        	if( num < 1) 
        	         return notify_fail("��Ҫ�����ΰ���\n");
        	else cost *= num;
        }
        
        if( me->query_skill(skill["name"], 1) < skill["min_skill"] )
                return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫���ˣ�û��ѧ���κζ�����\n");
        if( me->query_skill(skill["name"], 1) > skill["max_skill"] )
                return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");

        if( !me->query_skill(skill["name"], 1) ) me->set_skill(skill["name"], 0);

        my_skill = me->query_skill(skill["name"], 1);

        if( (int)me->query("jing") < cost ) {
        	if( num )
                        return notify_fail("�����ڵľ��������ж���ô��Ρ�\n");
                else return notify_fail("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
        }
        
        if( (string)SKILL_D(skill["name"])->type()=="martial"
           && my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                write("Ҳ����ȱ��ʵս���飬���"+ob->name()+"������˵�Ķ��������޷���ᡣ\n");
        else {
        	if( num ) str = "�㷴���ж����й�";
        	else str = "���ж����й�";
                if(zhao_name = SKILL_D(skill["name"])->query_skill_name(my_skill))
                        write(str+to_chinese(skill["name"])+"�ļ��ɣ��ԡ�"+zhao_name+"����һ���ƺ���Щ�ĵá�\n");
                else write(str+to_chinese(skill["name"])+"�ļ��ɣ��ƺ��е��ĵá�\n");
                me->improve_skill(skill["name"], ((int)me->query_skill("literate", 1)/5+1) * (num?num:1));
                if( num ) me->start_busy(1);
                }

        if (cost < 1) cost = 1;
        me->receive_damage("jing", cost );

        return 1;
}

int help(object me)
{
   write( @HELP
ָ���ʽ: study|du <��Ʒ����> [����]

���ָ��ʹ�����ͨ���Ķ����Ż�������Ʒ��ѧĳЩ����,
��ǰ����: �㲻���Ǹ�����ä����

see also : learn
HELP
   );
   return 1;
}
