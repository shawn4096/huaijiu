// bishen.c �Ա�֮����ʩ����
// by tiantian@sj

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int query_pfm(object me,object target);

mapping *tested=({
	([ "skill":"anran-zhang","number":2,"perform1":"anran","perform2":"xiaohun" ]),
	([ "skill":"banruo-zhang","number":2,"perform1":"qiankun","perform2":"yipai" ]),
	([ "skill":"canglang-goufa","number":2,"perform1":"beauty","perform2":"hero" ]),
	([ "skill":"chousui-zhang","number":5,"perform1":"yinhuo","perform2":"biyan",
	"perform3":"huoqiu","perform4":"huoqiang","perform5":"fushidu"]),
	([ "skill":"cihang-bian","number":1,"perform1":"cibei" ]),
	([ "skill":"cuixin-zhang","number":1,"perform1":"cuixin" ]),
	([ "skill":"dagou-bang","number":3,"perform1":"chan","perform2":"wugou","perform3":"linglong" ]),
	([ "skill":"dashou-yin","number":1,"perform1":"tianyin" ]),
	([ "skill":"duanjia-jianfa","number":1,"perform1":"fenglei" ]),
	([ "skill":"dugu-jiujian","number":3,"perform1":"po","perform2":"kuangfeng","perform3":"pozhang" ]),
	([ "skill":"fanliangyi-dao","number":1,"perform1":"sanshenfeng" ]),
	([ "skill":"fengmo-zhang","number":1,"perform1":"feizhang" ]),
//	([ "skill":"hama-gong","number":3,"perform1":"hama","perform2":"nizhuan","perform3":"qudu" ]),
	([ "skill":"hanbing-mianzhang","number":1,"perform1":"xixue" ]),
	([ "skill":"hanbing-shenzhang","number":1,"perform1":"hanbing" ]),
	([ "skill":"huagu-mianzhang","number":3,"perform1":"bujue","perform2":"huagu","perform3":"puhuo" ]),
	([ "skill":"huashan-jianfa","number":4,"perform1":"jianmang","perform2":"jianzhang","perform3":"wudui","perform4":"lianhuan" ]),
//	([ "skill":"huifeng-bian","number":1,"perform1":"huixuan" ]),
	([ "skill":"huifeng-jian","number":3,"perform1":"mie","perform2":"jue","perform3":"liaoyuan" ]),
	([ "skill":"hunyuan-zhang","number":1,"perform1":"wuji" ]),
//	([ "skill":"huoyan-dao","number":2,"perform1":"daoqi","perform2":"fen" ]),
	([ "skill":"jieshou-jiushi","number":1,"perform1":"foguang" ]),
	([ "skill":"jingang-quan","number":2,"perform1":"fumo","perform2":"qixing" ]),
	([ "skill":"jinshe-jianfa","number":1,"perform1":"kuangwu" ]),
	([ "skill":"jiuyin-baiguzhua","number":1,"perform1":"jiuyin" ]),
//	([ "skill":"jiuyin-shenzhang","number":2,"perform1":"shenzhang","perform2":"yinyang" ]),
//	([ "skill":"jiuyin-shenzhua","number":1,"perform1":"sanjue" ]),
//	([ "skill":"juehu-shou","number":1,"perform1":"juehu" ]),
//	([ "skill":"kongming-quan","number":1,"perform1":"berserk" ]),
	([ "skill":"kurong-changong","number":1,"perform1":"jiuchong"]),
	([ "skill":"lanhua-shou","number":1,"perform1":"fuxue" ]),
	([ "skill":"lietian-fu","number":1,"perform1":"lihun" ]),
	([ "skill":"lieyan-dao","number":1,"perform1":"shenghuo" ]),
	([ "skill":"lingshe-bianfa","number":2,"perform1":"chan","perform2":"sandou" ]),
	([ "skill":"liuhe-daofa","number":1,"perform1":"sancai" ]),
	([ "skill":"longzhua-gong","number":1,"perform1":"canyun" ]),
	([ "skill":"luoying-zhang","number":3,"perform1":"bading","perform2":"fugu","perform3":"pikong" ]),
	([ "skill":"nianhua-zhi","number":1,"perform1":"fuxue" ]),
//	([ "skill":"pixie-jian","number":3,"perform1":"cimu","perform2":"feiying","perform3":"jue" ]),
	([ "skill":"poyu-quan","number":1,"perform1":"leidong" ]),
	([ "skill":"qianye-shou","number":1,"perform1":"qianshou" ]),
	([ "skill":"qishang-quan","number":1,"perform1":"qishang" ]),
	([ "skill":"quanzhen-jianfa","number":1,"perform1":"qixing" ]),
	([ "skill":"ranmu-daofa","number":3,"perform1":"fenwo","perform2":"fentian","perform3":"shoudao" ]),
	([ "skill":"riyue-bian","number":3,"perform1":"chanrao","perform2":"fumoquan","perform3":"riyue" ]),
//	([ "skill":"riyue-lun","number":1,"perform1":"dazhuan" ]),
	([ "skill":"ruying-suixingtui","number":1,"perform1":"ruying" ]),
	([ "skill":"sanhua-zhang","number":1,"perform1":"sanhua" ]),
	([ "skill":"shenghuo-lingfa","number":3,"perform1":"duo","perform2":"ji","perform3":"xinmo" ]),
//	([ "skill":"shenghuo-lingfa","number":4,"perform1":"duo","perform2":"ji","perform3":"tisha","perform4":"xinmo" ]),
//	([ "skill":"shenlong-tuifa","number":1,"perform1":"zhuiming" ]),
	([ "skill":"songshan-jian","number":3,"perform1":"feiwu","perform2":"leiting","perform3":"longxiang" ]),
	([ "skill":"songyang-bian","number":1,"perform1":"luan" ]),
	([ "skill":"songyang-shou","number":1,"perform1":"yinyang" ]),
//	([ "skill":"taiji-jian","number":4,"perform1":"chan","perform2":"lian","perform3":"raozhi","perform4":"sanhuan" ]),
//	([ "skill":"taiji-quan","number":6,"perform1":"dongjing","perform2":"luanhuan",
//	"perform3":"ji","perform4":"zhen","perform5":"yinyang","perform6":"zhannian"]),
//	([ "skill":"tanzhi-shentong","number":3,"perform1":"qiankun","perform2":"huayu","perform3":"shentong" ]),
//	([ "skill":"tiezhang-zhangfa","number":2,"perform1":"tianlei","perform2":"zhangdao" ]),
//	([ "skill":"weituo-chu","number":2,"perform1":"leidong","perform2":"chaodu" ]),
	([ "skill":"xiangfu-lun","number":1,"perform1":"wushuai" ]),
//	([ "skill":"xianglong-zhang","number":2,"perform1":"paiyun","perform2":"xiao" ]),
	([ "skill":"xuanfeng-tui","number":1,"perform1":"kuangfeng" ]),
//	([ "skill":"xuantie-jianfa","number":2,"perform1":"haichao","perform2":"wujian" ]),
//	([ "skill":"xuedao-jing","number":2,"perform1":"jixue","perform2":"shendao" ]),
//	([ "skill":"yanxing-daofa","number":2,"perform1":"feiyan","perform2":"huanying" ]),
	([ "skill":"yingou-bifa","number":3,"perform1":"caoshu","perform2":"kaishu","perform3":"shigu" ]),
//	([ "skill":"yinlong-bian","number":2,"perform1":"feilong","perform2":"chanrao" ]),
//	([ "skill":"yinsuo-jinling","number":1,"perform1":"yueyin" ]),
//	([ "skill":"yiyang-zhi","number":1,"perform1":"yizhisanmai" ]),
//	([ "skill":"yizhi-chan","number":2,"perform1":"wofo","perform2":"qiankun" ]),
//	([ "skill":"yunu-jianfa","number":1,"perform1":"suxin" ]),
//	([ "skill":"yuxiao-jian","number":2,"perform1":"feiying","perform2":"qimen" ]),
//	([ "skill":"zhenshan-mianzhang","number":1,"perform1":"bingdi" ]),
//	([ "skill":"zhuihun-gou","number":1,"perform1":"luanpifeng" ]),
//	([ "skill":"zui-gun","number":1,"perform1":"zuijiu" ]),
	});

int perform(object me, object target)
{
	int i,j;
	object weapon,weapon2;
	string perform,perform_file;
	string skill;

	if( !target )
		target = offensive_target(me);
	if( !target || !me->is_fighting(target) ) 
		return notify_fail("�Ա�֮����ʩ����ֻ����ս����ʹ��!��\n");                
	if(me->query_temp("bishen_target"))
		return notify_fail("������ʹ���Ա�֮����ʩ����\n");
	if(me->query_temp("douzhuan_target")||me->query_temp("douzhuan_target"))
		return notify_fail("������ʹ�ö�ת���ơ�\n");

	weapon=me->query_temp("weapon");
	weapon2=target->query_temp("weapon");
	if( !(!weapon&&!weapon2)&& ((weapon&&!weapon2)
		|| (!weapon&&weapon2)
		|| weapon->query("skill_type")!=weapon2->query("skill_type") ) )
		return notify_fail("��ͶԷ��ı�����ͬ������ʹ���Ա�֮����ʩ����\n");

	if( target->query("family/family_name")=="����Ľ��"
		|| target->query_skill("douzhuan-xingyi",1)>0
		|| target->query_temp("bishen_target") )
		return notify_fail("�㲻����Է�ʹ���Ա�֮����ʩ����\n");

    if( (int)me->query("max_neili") < 2500 )
		return notify_fail("��������������ߣ�\n");
	if( (int)me->query("neili") < 2500 )
		return notify_fail("�㵱ǰ������������\n");
	if(me->query_skill("douzhuan-xingyi",1)<180 )
		return notify_fail("��Ķ�ת���Ʋ����������������Ա�֮����ʩ����\n");
	if( me->query("combat_exp")<target->query("combat_exp")/2
		|| me->query("max_neili")<target->query("max_neili")/4
		|| me->query("neili")<target->query("neili")/2 )
		return notify_fail("����书��Ϊ���Է����̫Զ��ǿ�������Ա�֮����ʩ�������������Լ���\n");

	i=query_pfm(me,target);
	if( i< 0 )
	{
		return 1;
	}
	skill=tested[i]["skill"];
	j=1+random(tested[i]["number"]);
	if(!me->query("env/"+skill))
		perform=tested[i]["perform"+sprintf("%d",j)];
	else
		perform=me->query("env/"+skill);

	if(!perform)
	{
		tell_object(me,"�����б���"+skill+"������֪ͨ��ʦ�޸ġ�\n");
		return 1;
	}

	if( file_size(SKILL_D(skill)+"/"+perform+".c")<1 )
	{
		tell_object(me,"�Է���ǰʹ�õ��书���⹦"+perform+"�Ѿ�ɾ������֪ͨ��ʦ�޸ġ�\n");
		return 1;
	}

	perform_file=SKILL_D(skill)+"/"+perform+".c";
	me->set_temp("bishen_target",target);

//	message_vision(HIG"$N���ù���Ľ�ݶ�ת���ƾ�������Ҫʹ��"+target->query("name")
//		+"�ĳ���������\n"NOR,me);

	call_out("remove_effect",1,me,target,skill,perform);
	if( skill=="canglang-goufa" )
	{
		me->set_temp("master",me->query("family/master_id"));
		me->set("family/master_id","hong antong");
	}
	else if( skill=="cihang-bian" )
	{
		me->set_temp("shen",me->query("shen"));
		me->set("shen",1000000);
	}
	else if(skill=="taiji-quan")
		me->set_temp("tjq/̫��",1);
	else if(skill=="taiji-jian" && perform=="raozhi")
		me->set("wd/raozhi",1);
	else if( skill=="anran-zhang" && perform=="anran" )
		target->add_temp("anran",2);
	else if( skill=="ruying-suixingtui" && perform=="ruying" )
		target->add_temp("sl_rysxt",5);
	else if( skill=="xuanfeng-tui" && perform=="kuangfeng" )
		me->set("thd/perform",4);
	else if( skill=="xianglong-zhang" && perform=="kanglong")
		me->set("xlz/hang",1);
	return (int)call_other( perform_file, "perform", me, target);
}

int remove_effect(object me,object target,string skill,string perform)
{
	if( !target || !me->is_fighting(target) )
	{
		me->delete_temp("bishen_target");
		me->delete_temp("tjq/̫��");
		me->delete("wd/raozhi");
		me->delete("thd/perform");
		me->delete("xlz/hang");
		return 0;
	}
	else if ( skill=="anran-zhang" && perform=="anran")
	{
		target->delete_temp("anran");
		me->delete_temp("bishen_target");
		return 0;
	}
	else if ( skill=="canglang-goufa")
	{
		me->set("family/master_id",me->query_temp("master"));
		me->delete_temp("master");
		me->delete_temp("bishen_target");
		return 0;
	}
	else if ( skill=="cihang-bian")
	{
		me->set("shen",me->query_temp("shen"));
		me->delete_temp("shen");
		me->delete_temp("bishen_target");
		return 0;
	}
	else if ( skill=="ruying-suixingtui" && perform=="ruying")
	{
		target->delete_temp("sl_rysxt");
		me->delete_temp("bishen_target");
		return 0;
	}
	else if( ( skill=="jingang-quan" && perform=="fumo" && me->query_temp("fumo") )
		|| ( skill=="banruo-zhang" && perform=="qiankun" && me->query_temp("sl/xiouliqiankun") )
		|| ( skill=="huashan-jianfa" && perform=="wudui" && me->query_temp("wudui") )
		|| ( skill=="kurong-changong" && perform=="jiuchong" && me->query_temp("pf_jiuchong") )
		|| ( skill=="lingshe-bianfa" && perform=="chan" && me->query_temp("lingshe/chan") )
		|| ( skill=="poyu-quan" && perform=="leidong" && me->query_temp("leidong") )
		|| ( skill=="riyue-bian" && perform=="chanrao" && me->query_temp("sl/chanrao") )
		|| ( skill=="shenghuo-lingfa" && perform=="ji" && me->query_temp("shlf_ji") )
		|| ( skill=="songyang-bian" && perform=="luan" && me->query_temp("ss_luan") )
		|| ( skill=="xianglong-zhang" && perform=="xiao" && me->query_temp("xlz/xiao") )
		|| ( skill=="anran-zhang" && perform=="xiaohun" && me->query_temp("xiaohun") )
		|| ( skill=="huashan-jianfa" && perform=="wudui" && me->query_temp("wudui") )
		|| ( skill=="taiji-jian" && perform=="chan" && me->query_temp("tjj/chan") )
		|| ( skill=="taiji-quan" && perform=="zhannian" && me->query_temp("tjq/zhannian") )
		|| ( skill=="suibo-zhuliu" && perform=="wuzhuan" && me->query_temp("thd/is_fast") )
		)
	{
		call_out("remove_effect",1,me,target,skill,perform);
		return 1;
	}
	else if( !me->is_perform() )
	{
		me->delete_temp("tjq/̫��");
		me->delete("wd/raozhi");
		me->delete_temp("bishen_target");
		me->delete("thd/perform");
		me->delete("xlz/hang");
		return 0;
	}
	else
		call_out("remove_effect",1,me,target,skill,perform);

	return 1;
}

int query_pfm(object me, object target)
{
	object weapon=target->query_temp("weapon");
	string skill,perform;
	int i;
	string *base_skill=({ "cuff","strike","hand","leg","claw","finger" });

	if(weapon)
	{
		skill=target->query_skill_mapped(weapon->query("skill_type"));
	}
	else
	{
		for(i=0;i<6;i++)
			if( (skill=target->query_skill_prepared(base_skill[i]) ) )
				break;
	}

	if( !skill 
		|| file_size(SKILL_D(skill)+".c") < 1 )
	{
		tell_object(me,"�Է���ǰʹ�õ��书��û���⹦�����޷��Ա�֮����ʩ����\n");
		return -1;
	}

	perform=SKILL_D(skill)->perform_action_file("");

	if(!stringp(perform) 
		|| sizeof( get_dir(perform) ) == 0 )
	{
		tell_object(me,"�Է���ǰʹ�õ��书��û���κ��⹦�����޷��Ա�֮����ʩ����\n");
		return -1;
	}

	for( i=0;i<sizeof(tested);i++)
		if( tested[i]["skill"]== skill )
			break;

	if(i==sizeof(tested))
	{
		tell_object(me,"�Է���ǰʹ�õ��书�е��⹦��û�о������ԣ����޷��Ա�֮����ʩ����\n");
		return -1;
	}

	return i;
}