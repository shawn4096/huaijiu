// learn.c

#include <skill.h>

inherit F_CLEAN_UP;

string *reject_msg = ({
	"˵������̫�����ˣ�����ô�ҵ���\n",
	"�������㼸�£�ҡ��ҡͷ��\n",
	"�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
	"Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string skill, teacher, skill_name;
	object ob;
	int i = 1, j, k;
	int master_skill, my_skill, gin_cost;

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (!arg ||
		(
			sscanf(arg, "%s %s %d", teacher, skill, i) != 3
			&& sscanf(arg, "%s from %s", skill, teacher) != 2
			&& sscanf(arg, "%s %s", teacher, skill) != 2
		)
	)
		return notify_fail("ָ���ʽ��learn|xue <ĳ��> <����> [����]\n");

	if( me->is_fighting() )
		return notify_fail("����ĥǹ������������\n");

	if( !(ob = present(teacher, environment(me))) || !ob->is_character() || ob->query("race") != "����")
		return notify_fail("��Ҫ��˭��̣�\n");

	if( !living(ob) )
		return notify_fail("��....����Ȱ�" + ob->name() + "Ū����˵��\n");    
      
	if( !master_skill = ob->query_skill(skill, 1) )
		return notify_fail("���������±����ұ���ѧ�ˡ�\n");

	if( (int)me->query("potential") < i || i < 1)
		return notify_fail("��û����ô��Ǳ����ѧϰ��û�а취�ٳɳ��ˡ�\n");

	if( i > 50 )
		return notify_fail("һ��ѧϰ��ô�࣬��û����һ�����ģ��ٵ�ɡ�\n");
	  
	notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );    
	for (j = 0; j < i; j++ ) {
		if( !me->is_apprentice_of(ob) 
		&& !(ob->recognize_apprentice(me)) 
		&&  me->query("marry/id") != ob->query("id"))
			return 0;
	}
	
	notify_fail(ob->name() + "��Ը���������ܡ�\n");
	
	if( me->query_skill(skill, 1) >= 220 && (string)SKILL_D(skill)->type() == "martial")
		return notify_fail("��������Ѿ��޷�ͨ��ѧϰ������ˡ�\n");
	
	if (me->query("marry/id") == ob->query("id")) {
		notify_fail(ob->name()+"����ɫ�е��ѿ����ƺ��ǲ��봫������������\n");
		if (me->query_skill(skill, 1) > ob->query_skill(skill, 1) - me->query("divorce") * 20)
			return 0;
                if (SKILL_D(skill)->valid_enable("force")
                && me->query("family/family_name") != ob->query("family/family_name"))
                        return 0;
	}
 
	if( ob->prevent_learn(me, skill) )
		return 0;

	my_skill = me->query_skill(skill, 1);
	if( my_skill >= master_skill )
		return notify_fail("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");

	notify_fail("����Ŀǰ��������û�а취ѧϰ���ּ��ܡ�\n");
	if( !SKILL_D(skill)->valid_learn(me) ) return 0;

	gin_cost = (90 + random(10)) / (int)me->query_int();

	if( !my_skill ) {
		gin_cost *= 2;
		me->set_skill(skill,0);
	}

	gin_cost += (me->query_skill(skill, 1)+1)/10;

	
	if ( i > 1 ) teacher = ob->name()+"����";
	else teacher = ob->name();
	
	write("����" + teacher + "����йء�" + to_chinese(skill) + "�������ʡ�\n");

	if( ob->query("env/no_teach") )
		return notify_fail("����" + ob->name() + "���ڲ���׼���ش�������⡣\n");

	gin_cost = i * gin_cost;
	if( userp(ob) ){
		tell_object(ob, me->name() + "��������йء�" + to_chinese(skill) + "�������ʡ�\n");
		if( (int)ob->query("jing") < gin_cost /5 + 10 ){
			write("����" + ob->name() + "��Ȼ̫���ˣ�û�а취����ʲô��\n");
			tell_object(ob, "������̫���ˣ�û�а취��" + me->name() + "��\n");
			return 1;
		}
		ob->receive_damage("jing", gin_cost /5 + 1);
	}
	
	if (random(10) == 9) 
		tell_room(environment(me), me->name() + "������" + ob->name() + "������⡣\n",({ me, ob }));		

	if( (int)me->query("jing") > gin_cost + 10 ) {
		if( (string)SKILL_D(skill)->type()=="martial"
		&& my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
			return notify_fail("Ҳ����ȱ��ʵս���飬���"+ob->name()+"�Ļش������޷���ᡣ\n");
		
		if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
			write("�㿪ʼ��ȡ"+teacher+"��ָ�����ԡ�"+skill_name+"����һ�н��п�˼��\n");
		else write("������"+teacher+"��ָ�����ƺ���Щ�ĵá�\n");
		me->add("potential", -i); 
		j = 0; k = i;
		while(i--) j += random(me->query_int() * 3 / 4) + random(my_skill / 10) + me->query_int() / 4;
		i = k;
		if( me->query("age") < 30 ){
			i *= ( 35 - me->query("age") ) / 3;
			if(me->query("age") <= 20)
				i *= 2;
		}
		j += ABS(i);      
		i = k;
		me->improve_skill(skill, j );
	}
	else {
		gin_cost = me->query("jing")-1;
		write("�����̫���ˣ����ʲôҲû��ѧ����\n");
	}

	me->receive_damage("jing", gin_cost);
	if( i > 1) me->start_busy(1);	   
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : learn|xue <ĳ��> <����> [����]

���ָ������������������й�ĳһ�ּ��ܵ��������⣬��Ȼ������̵Ķ�������
����ϵ�����������ߣ����㾭�����ַ�ʽѧϰ�����ļ���Ҳ�����ܸ��������
�̵��ˣ�Ȼ����Ϊ����ѧϰ��ʽ�൱�һ�֡�����Ĵ��С������ѧϰ����˵����Ϥ
һ���¼������ķ�����

����xue master force 10  -> �� master ����ѧ 10 �� force

���У��������Ϊ 50 �Ρ�

����ѧϰҲ��Ҫ����һЩ�����������ĵľ��������Լ�������ѧϰ����������йء�

�������ָ�� : apprentice, practice, skills, study
HELP
	);
	return 1;
}
