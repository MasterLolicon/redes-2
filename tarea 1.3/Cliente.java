import javax.swing.JFileChooser;
import java.net.*;
import java.io.*;

public class Cliente
{
	public static void main(String[] args)
	{
		try
		{
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Escriba la dirección del servidor: ");
			String host = br.readLine();
			System.out.println("\n\nEscriba el puerto: ");
			int pto = Integer.parseInt(br.readLine());
			Socket cl = new Socket(host,pto);
			JFileChooser jf = new JFileChooser();
			//
			jf.setMultiSelectionEnabled(true);
			//
			int r = jf.showOpenDialog(null);
			if(r == JFileChooser.APPROVE_OPTION)
			{
				File[] f=jf.getSelectedFiles();

				//

				double arc=f.length;
				DataOutputStream tama=new DataOutputStream(cl.getOutputStream());
				tama.writeDouble(arc);
				tama.close();

				DataOutputStream dos = new DataOutputStream(cl.getOutputStream());

				for(int i=0;i<arc;i++){
				//
				String archivo = f[i].getAbsolutePath();
				String nombre = f[i].getName();
				long tam = f[i].length();
				DataInputStream dis = new DataInputStream(new FileInputStream(archivo));
				dos.writeUTF(nombre);
				dos.flush();
				dos.writeLong(tam);
				dos.flush();
				byte[] b = new byte[1024];
				long enviados = 0;
				int porcentaje, n;
				while(enviados < tam)
				{
					n = dis.read(b);
					dos.write(b,0,n);
					dos.flush();
					enviados = enviados + n;
					porcentaje = (int)(enviados*100/tam);
					System.out.print("Enviado " + porcentaje + "%\r");
				}
				System.out.println("Archivo enviado\n");
				
				dis.close();
			}
			dos.close();
		 }

			br.close();
			cl.close();

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}