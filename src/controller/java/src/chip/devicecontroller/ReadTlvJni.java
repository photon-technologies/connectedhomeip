package chip.devicecontroller;

import chip.devicecontroller.model.NodeState;
import javax.annotation.Nullable;

/** JNI wrapper callback class for {@link ReportCallback}. */
public class ReadTlvJni {
    @Nullable private NodeState nodeState;

    public ReadTlvJni() {
        this.nodeState = new NodeState();
    }

    public NodeState getNodeState() {
        return nodeState;
      }

    public native void readReportData(byte[] data);

  static {
  System.out.println("Loading JNI library from: " +
                System.getProperty("java.library.path"));
    System.loadLibrary("CHIPController");
  }

  // TODO(#8578): Replace finalizer with PhantomReference.
  @SuppressWarnings("deprecation")
  protected void finalize() throws Throwable {
    super.finalize();

  }
}