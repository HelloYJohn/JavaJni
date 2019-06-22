package com.esgyn;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.IStartup;

public class ShowTime implements IStartup {

	@Override
	public void earlyStartup() {
		// TODO Auto-generated method stub
		Display.getDefault().syncExec(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				long eclipseStartTime =Long.parseLong(System.getProperty("eclipse.startTime"));
				long costTime = System.currentTimeMillis() - eclipseStartTime;
				Shell shell =Display.getDefault().getActiveShell();
				String msg="Eclipse 启动耗时: "+costTime+"ms";
				MessageDialog.openInformation(shell, "消息", msg);
			}
		});
	}
	
}
