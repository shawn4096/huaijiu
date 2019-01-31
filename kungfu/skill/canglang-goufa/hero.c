// hero Ӣ������
// 19991002001

#include <ansi.h>

inherit F_SSERVER;

int calc_damage(int,int);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,j,k,total,shen; 
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("��Ӣ�����С�ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("��Ӣ�����С�ֻ�а��˽���������ã�\n");

        if( objectp(weapon=me->query_temp("weapon")) ) {
                string *ids = weapon->parse_command_id_list();
                if (member_array("bishou", ids) == -1)                          
                        return notify_fail("���������ذ�ײ����á�Ӣ�����С���\n");
        }
        else {
                return notify_fail("���������ذ�ײ����á�Ӣ�����С���\n");
        }
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 150 )
                return notify_fail("��Ļ������ƻ���������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("ֻ��ʹ�û�������ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 150 )
                return notify_fail("��������ȷ�����������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 150 )
                return notify_fail("��Ĳ��˹�������������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("ֻ��ʹ�ò��˹���ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("��Ķ����󷨹������㣬�����á�Ӣ�����С���\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�Ӣ�����С���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á�Ӣ�����С���\n");      

        if(me->query("gender")!= "����") 
                return notify_fail("ֻ�����˲���ʹ�á�Ӣ�����С���\n");      

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á�Ӣ�����С���\n");

        target->start_busy(1);
        me->add("jingli",-100);
        me->add("neili",-200);

        i = (me->query_skill("hook", 1) + me->query_skill("strike", 1) + me->query_skill("leg", 1)) /3 ;
        j = (target->query_skill("force", 1) + target->query_skill("dodge", 1) + target->query_skill("parry", 1))/3;

        shen = me->query("shen");
        if ( shen >= 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
        if ( shen < 0 && - shen > me->query("combat_exp")) shen = - me->query("combat_exp"); 

        k = -shen / 3000;

        if(k > 1000) k=1000;
        if(k < -1000) k=-1000;

        i = i * (1000 + k/3)/1000;
        k = 1000 + random(k/2);

        if(wizardp(me)) tell_object(me,sprintf("\nattack: %d , parry: %d  , shen: %d \n",i,j,k));

        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ�����������֮����������Ӣ�����С�\n"NOR;

        if(random(me->query("combat_exp")) > target->query("combat_exp")/2) {
                me->start_busy(1);
                me->add("neili",- random(400)+400 );
                me->add("jingli",-random(200)+ 200);
                total = 0;
                msg += HIY "\n$Nʹ��һ�С�����ٶ�����һ����ɦ$nҸ�׼�ȪѨ���������֮�ʣ���һ��ͬ\n"+
                           "ʱ����$n���С��Ѩ������ˤ����ϡ�\n\n"NOR;
                i = calc_damage(me->query_skill("huagu-mianzhang",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��Ѩ" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIY "\n$Nʹ��һ�С�³������������ȼ�װ��$nߵͷ��ͻȻһ��������������$n����\n"+
                         "�������ֻһ���ƣ�����ץ��$n�ҽ����ף����ֱ��������$nС����һ��������$nͷ��\n"+
                         "���ϣ�����������\n"NOR;

                i = calc_damage(me->query_skill("canglang-goufa",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIY "\n$Nʹ��һ�С����ཱུ������������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�\n"+
                         "ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n\n"+
                         "̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR;

                i = calc_damage(me->query_skill("shenlong-tuifa",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "ͷ��" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(6,"��Ӣ�����С�");
        }
        else {
                msg += HIY "\n$Nʹ��һ�С�����ٶ�����һ����ɦ$nҸ�׼�ȪѨ���������֮�ʣ���һ��ͬ\nʱ����$n���С��Ѩ������ˤ����ϡ�\n"NOR;
                msg += "����$n������$N����ͼ��û���ϵ�������ææ���Ա�һ�������˹�ȥ��\n";
                msg +=HIY "\n$Nʹ��һ�С�³������������ȼ�װ��$nߵͷ��ͻȻһ��������������$n����\n"+
                          "�������ֻһ���ƣ�����ץ��$n�ҽ����ף����ֱ��������$nС����һ��������$nͷ��\n"+
                          "���ϣ�����������\n"NOR;
                msg += "$n����һ�������漴�侲�������ڿ�����һ��������$N���ţ�$Nֻ���ɿ����֡�\n";
                msg += HIY "\n$Nʹ��һ�С����ཱུ������������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�\n"+
                           "ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n\n"+
                           "̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR;
                msg += "$n��$N��ס������Σ���ң���������סҪ����ͬʱ�߸�Ծ�𣬷�����ͷײ�أ���$Nײ�˳�ȥ��\n";

                message_vision(msg,me,target);

                me->start_busy(1+random(3));
                me->start_perform(4,"��Ӣ�����С�");
        }

        return 1;
}

int calc_damage(int skill,int k)
{
        int i;

        if(skill>200)
                i = (200*3 + (skill-200)*4) * k/1000;
        else
                i = (skill * k/1000) * 5;

        i = i/2 + random(i/2);

        if(i > 800) i = 800;
        return i;
}
