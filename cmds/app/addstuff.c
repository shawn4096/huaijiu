// adstuff.c
// by snowman@SJ 20/05/1999

#include <ansi.h>
inherit F_CLEAN_UP;
int help(object me);

int main(object me, string arg)
{
	object ob;
	int num = 1;
            
	if( !arg || sscanf(arg, "%d %s", num, arg) != 2)
        	return help(me);
        
        if( !intp(num)) 
                return notify_fail("ע�⣺��������Ϊ���֡� \n");
        
        if( !objectp(ob = present(arg, environment(me))))
                if( !objectp(ob = present(arg, me)))
                       return notify_fail("����û�������Ʒ��\n");
         
        if( ob->is_character() )
		return notify_fail("�����һ�㣬�ǿ�������Ŷ��\n");
		
	if(file_size(base_name(ob)+".c") <= 0 )
		return notify_fail("�Բ��𣬴���Ʒ��Դ�ļ��Ѿ��������ˡ�\n");

	if( num <= 0 ){
		if(TASK_D->delete_status(ob->query("name")))
			return notify_fail("�㽫"+ob->name()+"("+ob->query("id")+") �� task_stuffs ��ɾ��....Ok��\n");
		else 	return notify_fail("��"+ob->name()+"��TASKD.C ��ɾ��ʧ�ܡ�\n");
	}
	else if(TASK_D->set_stuff(ob->query("name"), ([ "id" : ob->query("id"), "reward" : num ]) ))
		return notify_fail("�㽫"+ob->name()+"("+ob->query("id")+") ��EXP = "+num+" ���뵽 task_stuffs ��....Ok��\n");

	else return notify_fail("TASKD.C ���Ѿ����˴˼���Ʒ����Ҫ��������ɾ��\n");
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ��

adstuff <����> <��Ʒ>

����Ϊ��ֵ֮EXP��
�������Ϊ�㣬��ɾ������Ʒ��

by snowman@SJ 20/05/1999

HELP
    );
    return 1;
}

